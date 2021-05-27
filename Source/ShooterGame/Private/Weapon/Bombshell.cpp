// ShooterGame. All Right Reserved.

#include "Weapon/Bombshell.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(Log_Bombshell, All, All)

ABombshell::ABombshell()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(5.f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
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

        CollisionComponent->OnComponentHit.AddDynamic(this, &ABombshell::OnProjectileHit);
        SetLifeSpan(LifeSeconds);
    }
}

AController* ABombshell::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}

void ABombshell::OnProjectileHit(
    UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if(!ensure(GetWorld())) return;

    MovementComponent->StopMovementImmediately();

    // make radial Damage
    DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 32, FColor::Red, false, 5.f);
    if(UGameplayStatics::ApplyRadialDamage(this,  //
           DamageAmount,                          //
           GetActorLocation(),                    //
           DamageRadius,                          //
           UDamageType::StaticClass(),            //
           {GetOwner()},                          //
           this,                                  //
           GetController(),                       //
           DoFullDamage))
    {
        UE_LOG(Log_Bombshell, Warning, TEXT("I: %s got damage to someone"), *GetName())
        
    }

    Destroy();
}
