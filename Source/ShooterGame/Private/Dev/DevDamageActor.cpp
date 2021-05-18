// ShooterGame. All Right Reserved.


#include "Dev/DevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADevDamageActor::ADevDamageActor()
{
 	PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);


}

// Called when the game starts or when spawned
void ADevDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 32, SphereColor);
    UGameplayStatics::ApplyRadialDamage(this, Damage, GetActorLocation(),
         Radius, DamageType, {}, this, nullptr, DoFullDamage);
}

