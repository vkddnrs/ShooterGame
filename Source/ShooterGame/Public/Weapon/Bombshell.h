// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bombshell.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class AController;

UCLASS()
class SHOOTERGAME_API ABombshell : public AActor
{
	GENERATED_BODY()
	
public:	
	ABombshell();

    void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
    UPROPERTY(VisibleAnywhere, Category = Components)
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, Category = Components)
    UProjectileMovementComponent* MovementComponent;

    UPROPERTY(EditDefaultsOnly, Category = Damage)
    float DamageRadius = 200.f;

    UPROPERTY(EditDefaultsOnly, Category = Damage)
    float DamageAmount = 50.f;

    UPROPERTY(EditDefaultsOnly, Category = Damage)
    bool DoFullDamage = false;

    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float LifeSeconds = 5.f;

    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
        const FHitResult& Hit);

	virtual void BeginPlay() override;

private:
    AController* GetController() const;
    FVector ShotDirection;


};
