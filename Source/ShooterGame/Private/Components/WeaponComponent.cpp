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

	SpawnWeapon();
}

void UWeaponComponent::SpawnWeapon()
{
    if(!ensure(GetWorld())) return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if(!ensure(Character)) return;

    CurrentWeapon = GetWorld()->SpawnActor<ASG_BaseWeapon>(WeaponClass);
    if(!ensure(CurrentWeapon)) return;

    FAttachmentTransformRules AttachmentRule = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);        
    CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRule, WeaponAttachPointName);
    CurrentWeapon->SetOwner(Character); // for access at Character's Camera from WeaponClass
}

void UWeaponComponent::Fire()
{
    if(!ensure(CurrentWeapon)) return;
    CurrentWeapon->Fire();
}