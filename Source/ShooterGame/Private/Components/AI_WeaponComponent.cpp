// ShooterGame. All Right Reserved.


#include "Components/AI_WeaponComponent.h"
#include "SG_BaseWeapon.h"

void UAI_WeaponComponent::StartFire()
{
    if(!IsCanFire()) return;

    if(CurrentWeapon->IsAmmoEmpty())
    {
        NextWeapon();
    }
    else
    {
        CurrentWeapon->StartFire();
    }
}

void UAI_WeaponComponent::NextWeapon()
{
    if(!IsCanEquip()) return;
    int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();

    while (NextIndex != CurrentWeaponIndex)
    {
        // We go through the entire arsenal of weapons in search of where there are projectiles.
        if(!Weapons[NextIndex]->IsAmmoEmpty()) break; // The weapon has Ammo.

        NextIndex = (NextIndex + 1) % Weapons.Num();        
    }

    if(NextIndex != CurrentWeaponIndex)
    {
        //A weapon with ammunition has been found!
        CurrentWeaponIndex = NextIndex;
        EquipWeapon(CurrentWeaponIndex);
    }
}
