// ShooterGame. All Right Reserved.


#include "AI/SG_AIController.h"
#include "SG_AICharacter.h"
#include "Components/SG_AIPerceptionComponent.h"

ASG_AIController::ASG_AIController()
{
    SG_AIPerceptionComponent = CreateDefaultSubobject<USG_AIPerceptionComponent>("SG_AIPerceptionComponent");
    SetPerceptionComponent(*SG_AIPerceptionComponent);
}

void ASG_AIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    static auto SG_AICharacter = Cast<ASG_AICharacter>(InPawn);
    if(SG_AICharacter)
    {
        //RunBehaviorTree(SG_AICharacter->BehaviorTreeAsset);
    }
}

void ASG_AIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    const auto AimActor = Cast<USG_AIPerceptionComponent>(PerceptionComponent)->GetClosestEnemy();
    SetFocus(AimActor);
}
