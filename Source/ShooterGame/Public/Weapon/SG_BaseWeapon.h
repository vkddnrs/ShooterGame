// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SG_BaseWeapon.generated.h"

UCLASS()
class SHOOTERGAME_API ASG_BaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASG_BaseWeapon();

    void Fire();

protected:
    UPROPERTY(VisibleAnywhere, Category = Components)
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, Category = Setup)
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float TraceMaxDistance = 1500.f;

    virtual void BeginPlay() override;

    void MakeShot();

};
