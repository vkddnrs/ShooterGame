// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SG_BaseWeapon.h"
#include "LauncherWeapon.generated.h"

/**
 * 
 */

class ABombshell;

UCLASS()
class SHOOTERGAME_API ALauncherWeapon : public ASG_BaseWeapon
{
	GENERATED_BODY()

public:
    void StartFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = Projectile)
    TSubclassOf<ABombshell> ProjectileClass;	

    void MakeShot() override;
};
