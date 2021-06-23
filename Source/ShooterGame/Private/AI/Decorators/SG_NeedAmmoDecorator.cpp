// ShooterGame. All Right Reserved.


#include "AI/Decorators/SG_NeedAmmoDecorator.h"
#include "AIController.h"
#include "Components/WeaponComponent.h"
#include "SG_BaseWeapon.h"

USG_NeedAmmoDecorator::USG_NeedAmmoDecorator()
{
    NodeName = "Need Ammo";   
}

bool USG_NeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    if(!ensure(WeaponType)) return false;

    const auto Controller = OwnerComp.GetAIOwner();
    if(!Controller) return false;

    const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<UWeaponComponent>();
    if(!WeaponComponent) return false;

    return  WeaponComponent->NeedAmmo(WeaponType);
}
