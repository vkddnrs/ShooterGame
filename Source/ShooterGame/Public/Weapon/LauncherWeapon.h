// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SG_BaseWeapon.h"
#include "LauncherWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API ALauncherWeapon : public ASG_BaseWeapon
{
	GENERATED_BODY()

public:
    void StartFire() override;
    void StopFire() override;

protected:
    void MakeShot() override;
};
