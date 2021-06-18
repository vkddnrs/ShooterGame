// ShooterGame. All Right Reserved.


#include "AI/Services/SG_FindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SG_AIPerceptionComponent.h"
#include "AIController.h"

USG_FindEnemyService::USG_FindEnemyService()
{
    NodeName = "Find Enemy";
}

void USG_FindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    if(Blackboard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = Controller->FindComponentByClass<USG_AIPerceptionComponent>();
        if(PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
