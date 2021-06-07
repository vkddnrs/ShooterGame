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
protected:
    // The amount of health's points that can be taken at one time.
    UPROPERTY(EditAnywhere, Category = Pickup, meta = (ClampMin = 1.0, ClampMax = 500.f))
    float HealthAmount = 50.f;

private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;

	
};
