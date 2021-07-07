// ShooterGame. All Right Reserved.


#include "Menu/UI/SG_MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USG_MenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USG_MenuWidget::OnStartGame);
    }

}

void USG_MenuWidget::OnStartGame()
{
    const FName StartupLevelName = "TestLevel";
    UGameplayStatics::OpenLevel(this, StartupLevelName);
}
