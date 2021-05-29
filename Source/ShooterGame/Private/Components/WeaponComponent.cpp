// ShooterGame. All Right Reserved.


#include "Components/WeaponComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/SG_BaseWeapon.h"
#include "Animations/EquipFinishedAnimNotify.h"

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

ACharacter* UWeaponComponent::GetCharacter()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    return Character;
}

void UWeaponComponent::SpawnWeapons()
{
    ACharacter* Character = GetCharacter();
    if(!ensure(GetWorld() || !ensure(Character))) return;

    for (auto WeaponClass : WeaponClasses)
    {
        auto Weapon = GetWorld()->SpawnActor<ASG_BaseWeapon>(WeaponClass);
        if(!Weapon) continue;

        Weapon->SetOwner(Character);
        Weapons.Add(Weapon); // for access at Character's Camera from WeaponClasses
        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmourySocketName);
    }
}

void UWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
    ACharacter* Character = GetCharacter();
    if(!ensure(GetWorld()))  return;

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
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if(!ensure(GetWorld() || !ensure(Character))) return;

    // если CurrentWeapon уже существует, то его надо вернуть в положение за спиной
    if(CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmourySocketName);
        
    }

    CurrentWeapon = Weapons[WeaponIndex];
    if(ensure(CurrentWeapon))
    {
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
        PlayAnimMontage(EquipAnimMontage);
        bEquipAnimInProgress = true;
    }
}

void UWeaponComponent::NextWeapon()
{
    if(bEquipAnimInProgress) return;
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
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
    if(!ensure(EquipAnimMontage)) return;
    const auto NotifyEvents = EquipAnimMontage->Notifies;
    for (auto NotifyEvent : NotifyEvents)
    {
        auto EquipFinishedNotify = Cast<UEquipFinishedAnimNotify>(NotifyEvent.Notify);
        if(EquipFinishedNotify)
        {
            EquipFinishedNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnEquipFinished);
	        break;
        }
    }
}

void UWeaponComponent::OnEquipFinished(USkeletalMeshComponent* SkeletalMesh)
{
    if(GetCharacter()->GetMesh() != SkeletalMesh) return;
  
    UE_LOG(Log_WeaponComponent, Display, TEXT("Equip finished"))
    bEquipAnimInProgress = false;    
}

bool UWeaponComponent::IsCanFire() const
{
    return !bEquipAnimInProgress && CurrentWeapon;
}

bool UWeaponComponent::IsCanEquip() const
{
    return !bEquipAnimInProgress;
}
