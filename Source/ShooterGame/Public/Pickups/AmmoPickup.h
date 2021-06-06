// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "AmmoPickup.generated.h"

/**
 * 
 */

class ASG_BaseWeapon;

UCLASS()
class SHOOTERGAME_API AAmmoPickup : public ABasePickup
{
	GENERATED_BODY()

protected:
    // The number of clips that can be taken at one time.
    UPROPERTY(EditAnywhere, Category = Pickup, meta = (ClampMin = 1, ClampMax = 10))
    int32 ClipsAmount = 10;

    // Ammunition for which type of weapon this pickup provides.
    UPROPERTY(EditAnywhere, Category = Pickup)
    TSubclassOf<ASG_BaseWeapon> WeaponType;

private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
