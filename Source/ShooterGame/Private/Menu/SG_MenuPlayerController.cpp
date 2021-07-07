// ShooterGame. All Right Reserved.


#include "Menu/SG_MenuPlayerController.h"
#include "SG_GameInstance.h"

void ASG_MenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;


}
