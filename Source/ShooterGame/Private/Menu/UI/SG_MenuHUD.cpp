// ShooterGame. All Right Reserved.


#include "Menu/UI/SG_MenuHUD.h"
#include "Blueprint/UserWidget.h"

void ASG_MenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if(ensureAlways(GetWorld() && MenuWidgetClass))
    {
        const auto MenuWidget = CreateWidget(GetWorld(), MenuWidgetClass, "MainMenu");

        if(MenuWidget)
        {
            MenuWidget->AddToViewport();
        }
    }
}
