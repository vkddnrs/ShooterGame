// ShooterGame. All Right Reserved.


#include "SG_PlayerController.h"
#include "Components/SG_RespawnComponent.h"

ASG_PlayerController::ASG_PlayerController()
{
    RespawnComponent = CreateDefaultSubobject<USG_RespawnComponent>("RespawnComponent");
}

void ASG_PlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    OnNewPawn.Broadcast(InPawn); // in case of a possible bug, when this method will not be called in the base class
}
