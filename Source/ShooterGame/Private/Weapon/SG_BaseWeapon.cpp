// ShooterGame. All Right Reserved.


#include "Weapon/SG_BaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

// Sets default values
ASG_BaseWeapon::ASG_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);

}

// Called when the game starts or when spawned
void ASG_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASG_BaseWeapon::Fire()
{
    UE_LOG(LogBaseWeapon, Display, TEXT("Fire!"))
}


