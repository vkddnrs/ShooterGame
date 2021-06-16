// ShooterGame. All Right Reserved.


#include "AI/SG_AIController.h"
#include "SG_AICharacter.h"

void ASG_AIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    static auto SG_AICharacter = Cast<ASG_AICharacter>(InPawn);
    if(SG_AICharacter)
    {
        RunBehaviorTree(SG_AICharacter->BehaviorTreeAsset);
    }
}
