// ShooterGame. All Right Reserved.


#include "UI/SG_GoToMenuWidget.h"
#include "SG_GameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSG_GoToMenuWidget, All, All)

void USG_GoToMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(GoToMenuButton)
    {
        GoToMenuButton->OnClicked.AddDynamic(this, &USG_GoToMenuWidget::OnGoToMenu);
    }
}

void USG_GoToMenuWidget::OnGoToMenu()
{
    if(!ensure(GetWorld())) return;

    const auto GameInstance = Cast<USG_GameInstance>(GetWorld()->GetGameInstance());
    if(!GameInstance || GameInstance->GetMainMenuLevelName().IsNone())
    {
        UE_LOG(LogSG_GoToMenuWidget, Error, TEXT("Menu level name is None"))
        return;
    }

    UGameplayStatics::OpenLevel(GetWorld(), GameInstance->GetMainMenuLevelName());
}
