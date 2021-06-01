// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SG_BaseWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature)

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    int32 Bullets;

    UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "!bInfinite"))
    int32 Clips;

    UPROPERTY(EditDefaultsOnly)
    bool bInfinite = false;
};

UCLASS()
class SHOOTERGAME_API ASG_BaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASG_BaseWeapon();

    FOnClipEmptySignature OnClipEmpty;
    virtual void StartFire();
    virtual void StopFire();

    void ChangeClip();
    bool IsCanReload() const;

protected:
    UPROPERTY(VisibleAnywhere, Category = Components)
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, Category = Setup)
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, Category = Setup)
    float TraceMaxDistance = 1500.f;

    UPROPERTY(EditDefaultsOnly, Category = Shot)
    float DamageAmount = 10.f;

    UPROPERTY(EditDefaultsOnly, Category = AmmoData)
    FAmmoData DefaultsAmmo{15, 10, false};

    virtual void BeginPlay() override;

    virtual void MakeShot();
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

    APlayerController* GetPlayerController() const;
    bool GetPlayerViewpoint(FVector& ViewLocation, FRotator& ViewRotation) const;

    // Point of projectile's spawn. 
    FVector GetMuzzleWorldLocation() const;

    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;
    void MakeDamage(const FHitResult& HitResult);

    void DecreaseAmmo();
    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;    
    void LogAmmo();
    

private:
    FAmmoData CurrentAmmo;


};
