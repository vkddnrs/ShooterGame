// ShooterGame. All Right Reserved.


#include "Menu/SG_MenuGameModeBase.h"
#include "Menu/SG_MenuPlayerController.h"
#include "Menu/UI/SG_MenuHUD.h"


ASG_MenuGameModeBase::ASG_MenuGameModeBase()
{
    PlayerControllerClass = ASG_MenuPlayerController::StaticClass();
    HUDClass = ASG_MenuHUD::StaticClass();
}
