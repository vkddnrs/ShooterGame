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

bool ABasePickup::CouldBeTaken() const
{
    //return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
    return bCouldBeTakenTest;
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();

    ensure(CollisionComponent);
    ensure(GetRootComponent());

    GetRandomRotationYaw();
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if(GivePickupTo(Pawn))
    {
        PickupWasTaken();
    }
}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    AddActorLocalRotation(FRotator(0.f, RotationYaw, 0.f));
}

bool ABasePickup::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void ABasePickup::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    GetRootComponent()->SetVisibility(false, true);

    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ABasePickup::Respawn, RespawnTime, false);
}

void ABasePickup::Respawn()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    GetRootComponent()->SetVisibility(true, true);
    GetRandomRotationYaw();
}

void ABasePickup::GetRandomRotationYaw()
{
    const float Direction = FMath::RandBool() ? 1.f : -1.f;
    RotationYaw = FMath::RandRange(1.f, 2.f) * Direction;
}

