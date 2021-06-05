// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API AHealthPickup : public ABasePickup
{
	GENERATED_BODY()

private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;

	
};
