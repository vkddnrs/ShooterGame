// ShooterGame. All Right Reserved.


#include "Pickups/AmmoPickup.h"
#include "Components/HealthComponent.h"
#include "Components/WeaponComponent.h"
#include "ProjectUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All)

bool AAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = ProjectUtils::GetPlayerComponent<UHealthComponent>(PlayerPawn);
    if(!HealthComponent || HealthComponent->IsDead()) return false;

    const auto WeaponComponent = ProjectUtils::GetPlayerComponent<UWeaponComponent>(PlayerPawn);
    if(!WeaponComponent) return false;

    if(WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount))
    {
        UE_LOG(LogAmmoPickup, Display, TEXT("Ammo was taken"))
        return true;
    }
    return false;
}
