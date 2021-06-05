// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "AmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API AAmmoPickup : public ABasePickup
{
	GENERATED_BODY()
private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
