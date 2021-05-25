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

    virtual void StartFire();
    virtual void StopFire();

protected:
    UPROPERTY(VisibleAnywhere, Category = Components)
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, Category = Setup)
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float TraceMaxDistance = 1500.f;

    UPROPERTY(EditDefaultsOnly, Category = Shot)
    float DamageAmount = 10.f;

    virtual void BeginPlay() override;

    virtual void MakeShot();
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

    APlayerController* GetPlayerController() const;
    bool GetPlayerViewpoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;
    void MakeDamage(const FHitResult& HitResult);



};
