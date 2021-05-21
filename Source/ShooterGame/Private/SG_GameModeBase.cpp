// ShooterGame. All Right Reserved.


#include "SG_GameModeBase.h"
#include "SG_PlayerController.h"
#include "SG_BaseCharacter.h"
#include "UI/GameHUD.h"


ASG_GameModeBase::ASG_GameModeBase()
{
    // override of defold propertys
    DefaultPawnClass = ASG_BaseCharacter::StaticClass();
    PlayerControllerClass = ASG_PlayerController::StaticClass();
    HUDClass = AGameHUD::StaticClass();
}
