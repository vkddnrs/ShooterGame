// ShooterGame. All Right Reserved.


#include "Menu/UI/SG_MenuHUD.h"
#include "UI/SG_BaseWidget.h"

void ASG_MenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if(ensureAlways(GetWorld() && MenuWidgetClass))
    {
        const auto MenuWidget = CreateWidget<USG_BaseWidget>(GetWorld(), MenuWidgetClass, "MainMenu");

        if(MenuWidget)
        {
            MenuWidget->AddToViewport();
            MenuWidget->Show();
        }
    }
}
