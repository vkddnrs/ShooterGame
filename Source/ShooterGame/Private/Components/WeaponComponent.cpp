// ShooterGame. All Right Reserved.

#include "Components/WeaponComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/SG_BaseWeapon.h"
#include "Animations/EquipFinishedAnimNotify.h"
#include "Animations/ReloadFinishedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(Log_WeaponComponent, All, All)

UWeaponComponent::UWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    CurrentWeaponIndex = 0;
    InitAnimations();
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for(auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();

    Super::EndPlay(EndPlayReason);
}

void UWeaponComponent::OnClipEmpty()
{
    ChangeClip();
}

void UWeaponComponent::ChangeClip()
{
    if(!IsCanReload()) return;
    CurrentWeapon->StopFire();
    CurrentWeapon->ChangeClip();
    bReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}

ACharacter* UWeaponComponent::GetCharacter() const
{
    return Cast<ACharacter>(GetOwner());
}

void UWeaponComponent::SpawnWeapons()
{
    ACharacter* Character = GetCharacter();
    if(!ensure(GetWorld() || !ensure(Character))) return;

    for(auto OneWeaponData : WeaponData)
    {
        auto Weapon = GetWorld()->SpawnActor<ASG_BaseWeapon>(OneWeaponData.WeaponClass);
        if(!Weapon) continue;

        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);  // for access at Character's Camera from WeaponClasses
        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmourySocketName);

        Weapon->OnClipEmpty.AddUObject(this, &UWeaponComponent::OnClipEmpty);
    }
}

void UWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
    ACharacter* Character = GetCharacter();
    if(!ensure(GetWorld())) return;

    Character->PlayAnimMontage(Animation);
}

void UWeaponComponent::AttachWeaponToSocket(ASG_BaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& WeaponSocketName)
{
    if(!ensure(Weapon || SceneComponent)) return;

    FAttachmentTransformRules AttachmentRule = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRule, WeaponSocketName);
}

void UWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    if(!IsCanEquip()) return;
    if(WeaponIndex < 0 || WeaponIndex >= Weapons.Num()) return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if(!ensure(GetWorld() || !ensure(Character))) return;

    // ���� CurrentWeapon ��� ����������, �� ��� ���� ������� � ��������� �� ������
    if(CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmourySocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    // CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
    const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) {  //
        return Data.WeaponClass == CurrentWeapon->GetClass();
    });  //
    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

    if(ensure(CurrentWeapon))
    {
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
        PlayAnimMontage(EquipAnimMontage);
        bEquipAnimInProgress = true;
    }
}

void UWeaponComponent::NextWeapon()
{
    if(!IsCanEquip()) return;
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::Reload()
{
    ChangeClip();
}

void UWeaponComponent::StartFire()
{
    if(!IsCanFire()) return;
    CurrentWeapon->StartFire();
}

void UWeaponComponent::StopFire()
{
    if(!ensure(CurrentWeapon)) return;
    CurrentWeapon->StopFire();
}

void UWeaponComponent::InitAnimations()
{
    auto EquipFinishedNotify = FindNotifyByClass<UEquipFinishedAnimNotify>(EquipAnimMontage);
    if(EquipFinishedNotify) EquipFinishedNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnEquipFinished);

    for(auto OneWeaponData : WeaponData)
    {
        auto ReloadFinishedNotify = FindNotifyByClass<UReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
        if(ReloadFinishedNotify) ReloadFinishedNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnReloadFinished);
    }
}

void UWeaponComponent::OnEquipFinished(USkeletalMeshComponent* SkeletalMesh)
{
    if(GetCharacter()->GetMesh() != SkeletalMesh) return;

    UE_LOG(Log_WeaponComponent, Display, TEXT("Equip finished"))
    bEquipAnimInProgress = false;
}

void UWeaponComponent::OnReloadFinished(USkeletalMeshComponent* SkeletalMesh)
{
    if(GetCharacter()->GetMesh() != SkeletalMesh) return;

    UE_LOG(Log_WeaponComponent, Display, TEXT("Reload finished"))
    bReloadAnimInProgress = false;
}

bool UWeaponComponent::IsCanFire() const
{
    return CurrentWeapon && !bEquipAnimInProgress && !bReloadAnimInProgress;
}

bool UWeaponComponent::IsCanEquip() const
{
    return !bEquipAnimInProgress && !bReloadAnimInProgress;
}

bool UWeaponComponent::IsCanReload() const
{
    return CurrentWeapon                     //
           && !bReloadAnimInProgress         //
           && !bEquipAnimInProgress          //
           && CurrentWeapon->IsCanReload();  //
}
