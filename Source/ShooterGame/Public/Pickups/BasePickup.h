// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTERGAME_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasePickup();

protected:
    UPROPERTY(VisibleAnywhere, Category = Components)
    USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere, Category = Respawn)
    float RespawnTime = 5.f;

	virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    virtual bool GivePickupTo(APawn* PlayerPawn); 

public:	
	virtual void Tick(float DeltaTime) override;

private:    
    void PickupWasTaken();
    void Respawn();
    void GetRandomRotationYaw();
    float RotationYaw;

};
