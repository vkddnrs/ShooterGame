// ShooterGame. All Right Reserved.


#include "Components/WeaponComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/SG_BaseWeapon.h"


UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

    CurrentWeaponIndex = 0;
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

void UWeaponComponent::SpawnWeapons()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
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
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmourySocketName);
        CurrentWeapon->StopFire();
    }

    CurrentWeapon = Weapons[WeaponIndex];
    if(ensure(CurrentWeapon))
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
}

void UWeaponComponent::NextWeapon()
{
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::StartFire()
{
    if(!ensure(CurrentWeapon)) return;
    CurrentWeapon->StartFire();
}

void UWeaponComponent::StopFire()
{
    if(!ensure(CurrentWeapon)) return;
    CurrentWeapon->StopFire();
}
