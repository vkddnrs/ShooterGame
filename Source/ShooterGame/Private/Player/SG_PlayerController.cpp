// ShooterGame. All Right Reserved.


#include "SG_PlayerController.h"
#include "Components/SG_RespawnComponent.h"

ASG_PlayerController::ASG_PlayerController()
{
    RespawnComponent = CreateDefaultSubobject<USG_RespawnComponent>("RespawnComponent");
}
