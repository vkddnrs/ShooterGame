// ShooterGame. All Right Reserved.


#include "Weapon/Bombshell.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(Log_Bombshell, All, All)

ABombshell::ABombshell()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(5.f);
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 2000.f;
    MovementComponent->ProjectileGravityScale = 0.f;
}

void ABombshell::BeginPlay()
{
	Super::BeginPlay();

    if(ensure(MovementComponent))
    {
        MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
        if(MovementComponent->InitialSpeed == 0.f)
	         UE_LOG(Log_Bombshell, Warning, TEXT("MovementComponent.InitialSpeed dont be 0.f amount !!!"))
        if(MovementComponent->ProjectileGravityScale == 1.f)
            UE_LOG(Log_Bombshell, Warning, TEXT("MovementComponent.ProjectileGravityScale should be 0.f amount !!!"))

    }

}



