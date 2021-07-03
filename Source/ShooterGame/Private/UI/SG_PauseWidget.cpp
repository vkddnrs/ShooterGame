// ShooterGame. All Right Reserved.


#include "UI/SG_PauseWidget.h"
#include "SG_GameModeBase.h"
#include "Components/Button.h"

bool USG_PauseWidget::Initialize()
{
    const auto InitStatus = Super::Initialize();
    if(ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &USG_PauseWidget::OnClearPause);
    }

    return InitStatus;
}

void USG_PauseWidget::OnClearPause()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();

}
