// ShooterGame. All Right Reserved.


#include "AI/SG_AIController.h"
#include "SG_AICharacter.h"
#include "Components/SG_AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ASG_AIController::ASG_AIController()
{
    SG_AIPerceptionComponent = CreateDefaultSubobject<USG_AIPerceptionComponent>("SG_AIPerceptionComponent");
    SetPerceptionComponent(*SG_AIPerceptionComponent);

    bWantsPlayerState = true;
}

void ASG_AIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if(const auto SG_AICharacter = Cast<ASG_AICharacter>(InPawn))
    {
        RunBehaviorTree(SG_AICharacter->BehaviorTreeAsset);
    }
}

void ASG_AIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    const auto AimActor = GetFocusOnActor();
    SetFocus(AimActor);
}

AActor* ASG_AIController::GetFocusOnActor() const
{
    if(!GetBlackboardComponent()) return nullptr;
    return Cast<AActor>( GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
