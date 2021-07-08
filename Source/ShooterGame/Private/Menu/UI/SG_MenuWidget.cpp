// ShooterGame. All Right Reserved.


#include "Menu/UI/SG_MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SG_GameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogSG_MenuWidget, All, All)

void USG_MenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USG_MenuWidget::OnStartGame);
    }

    if(QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &USG_MenuWidget::OnQuitGame);
    }
}

void USG_MenuWidget::OnStartGame()
{
    if(!GetWorld()) return;

    const auto GameInstance = GetWorld()->GetGameInstance<USG_GameInstance>();
    if(!GameInstance) return;

    if(GameInstance->GetStartupLevelName().IsNone())
    {
        UE_LOG(LogSG_MenuWidget, Error, TEXT("Level Name is None"))
        return;
    }

    UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevelName());
}

void USG_MenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
