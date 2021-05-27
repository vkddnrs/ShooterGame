// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bombshell.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOTERGAME_API ABombshell : public AActor
{
	GENERATED_BODY()
	
public:	
	ABombshell();

    void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
    UPROPERTY(VisibleDefaultsOnly, Category = Collision)
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = Components)
    UProjectileMovementComponent* MovementComponent;


	virtual void BeginPlay() override;

private:
    FVector ShotDirection;

};
