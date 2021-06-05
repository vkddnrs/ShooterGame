// ShooterGame. All Right Reserved.


#include "Pickups/BasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All)

// Sets default values
ABasePickup::ABasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    SetRootComponent(CollisionComponent);
    CollisionComponent->InitSphereRadius(50.0);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    

}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    UE_LOG(LogBasePickup, Display, TEXT("Pickup was taken"))
    Destroy();
}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

