// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SG_BaseWeapon.h"
#include "RifleWeapon.generated.h"

class UWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class SHOOTERGAME_API ARifleWeapon : public ASG_BaseWeapon
{
	GENERATED_BODY()

public:
    ARifleWeapon();
    void StartFire() override;
    void StopFire() override;
    virtual void Zoom(bool Enabled) override;
    bool IsAmmoInfinit() const { return CurrentAmmo.bInfinite; }

protected:
    UPROPERTY(EditDefaultsOnly, Category = Weapon)
    float TimeBetweenShots = 0.1f;

    // Dispersion of shot direction.
    UPROPERTY(EditDefaultsOnly, Category = Weapon)
    float BulletSpread = 1.5f;

    UPROPERTY(EditDefaultsOnly, Category = VFX)
    UNiagaraSystem* TraceFX;

    UPROPERTY(EditDefaultsOnly, Category = VFX)
    FName TraceTargetName = "TraceTarget";

    UPROPERTY(VisibleAnywhere, Category = VFX)
    UWeaponFXComponent* WeaponFXComponent;

    virtual void BeginPlay() override;
    void MakeShot() override;
    void MakeDamage(const FHitResult& HitResult);
    bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;


private:
    FTimerHandle ShotTimerHandle;

    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent;

    UPROPERTY()
    UAudioComponent* FireAudioComponent;

    void InitFX(); // init of FX and sound
    void SetFXVActive(bool IsActive); // handle of FX and sound
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
    AController* GetController() const;

};
