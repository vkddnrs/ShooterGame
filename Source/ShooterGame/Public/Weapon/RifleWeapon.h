// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SG_BaseWeapon.h"
#include "RifleWeapon.generated.h"

/**
 * 
 */

class UWeaponFXComponent;

UCLASS()
class SHOOTERGAME_API ARifleWeapon : public ASG_BaseWeapon
{
	GENERATED_BODY()

public:
    ARifleWeapon();
    void StartFire() override;
    void StopFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = Shot)
    float TimeBetweenShots = 0.1f;

    // Dispersion of shot direction.
    UPROPERTY(EditDefaultsOnly, Category = Shot)
    float BulletSpread = 1.5f;

    UPROPERTY(VisibleAnywhere, Category = VFX)
    UWeaponFXComponent* WeaponFXComponent;

    virtual void BeginPlay() override;
    void MakeShot() override;
    bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;


private:
    FTimerHandle ShotTimerHandle;
};
