// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WeaponComponent.h"
#include "AI_WeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UAI_WeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void NextWeapon() override;
};
