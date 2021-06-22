// ShooterGame. All Right Reserved.


#include "AI/Decorators/SG_HealtnPercentDecorator.h"
#include "AIController.h"
#include "Components/HealthComponent.h"

USG_HealtnPercentDecorator::USG_HealtnPercentDecorator()
{
    NodeName = "Health Percent";
}

bool USG_HealtnPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(!Controller) return false;

    const auto Pawn = Controller->GetPawn();
    if(!Pawn) return false;

    const auto HealthComponent = Pawn->FindComponentByClass<UHealthComponent>();
    if(!HealthComponent || HealthComponent->IsDead()) return false; 

    return HealthComponent->GetHealthPercent() <= HealthPercentThreshold;
}
