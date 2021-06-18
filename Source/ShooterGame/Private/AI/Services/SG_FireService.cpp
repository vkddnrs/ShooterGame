// ShooterGame. All Right Reserved.


#include "AI/Services/SG_FireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WeaponComponent.h"
#include "AIController.h"


USG_FireService::USG_FireService()
{
    NodeName = "Fire";
}

void USG_FireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    const bool bHasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if(Controller)
    {
        const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<UWeaponComponent>();
        if(WeaponComponent)
        {
            bHasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
