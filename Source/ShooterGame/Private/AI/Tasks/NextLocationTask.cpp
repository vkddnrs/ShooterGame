// ShooterGame. All Right Reserved.


#include "AI/Tasks/NextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

UNextLocationTask::UNextLocationTask()
{
    NodeName = "Next Location";
}

EBTNodeResult::Type UNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto AIController = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    const auto Pawn = AIController->GetPawn();
    const auto NavSystem = UNavigationSystemV1::GetCurrent(Pawn); 
    if(!ensure(AIController || Blackboard || Pawn || NavSystem)) return EBTNodeResult::Failed;

    FNavLocation NavLocation;
    auto Location = Pawn->GetActorLocation();
    if(!bSelfCenter)
    {
        auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
        if(!CenterActor) return EBTNodeResult::Failed;
        Location = CenterActor->GetActorLocation();
    }

    bool Find = NavSystem->GetRandomReachablePointInRadius(Location, Radius, NavLocation);
    if(!Find) return EBTNodeResult::Failed;

    Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);

    return EBTNodeResult::Succeeded;
}