// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGCoreTypes.h"
#include "SG_BaseWeapon.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

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
    bool TryToAddAmmo(int32 ClipsAmount);
    bool IsAmmoEmpty() const;

    FWeaponUIData GetCurrentWeaponUIData() const { return WeaponUIData; }
    FAmmoData GetCurrentAmmoData() const { return CurrentAmmo;  }

protected:
    UPROPERTY(VisibleAnywhere, Category = Components)
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, Category = Weapon)
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, Category = Weapon)
    float TraceMaxDistance = 1500.f;

    UPROPERTY(EditDefaultsOnly, Category = Weapon)
    float DamageAmount = 10.f;

    UPROPERTY(EditDefaultsOnly, Category = Weapon)
    FAmmoData DefaultsAmmo{15, 10, false};

    UPROPERTY(EditDefaultsOnly, Category = UI)
    FWeaponUIData WeaponUIData;

    UPROPERTY(EditDefaultsOnly, Category = VFX)
    UNiagaraSystem* MuzzleFX;

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
    bool IsClipEmpty() const;
    bool IsAmmoFull() const;

    void LogAmmo();

    UNiagaraComponent* SpawnMuzzleFX();

private:
    FAmmoData CurrentAmmo;


};
