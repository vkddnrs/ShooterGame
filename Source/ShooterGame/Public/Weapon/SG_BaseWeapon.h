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

protected:
    UPROPERTY(VisibleAnywhere, Category = Components)
    USkeletalMeshComponent* WeaponMesh;

    virtual void BeginPlay() override;

public:	


};
