// ShooterGame. All Right Reserved.


#include "Pickups/HealthPickup.h"
#include "Components/HealthComponent.h"
#include "ProjectUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All)

bool AHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = ProjectUtils::GetPlayerComponent<UHealthComponent>(PlayerPawn);

    if(!HealthComponent || HealthComponent->IsDead()) return false;

    return HealthComponent->TryAddHealthAmount(HealthAmount);
}
