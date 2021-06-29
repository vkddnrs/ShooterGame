// ShooterGame. All Right Reserved.


#include "UI/SG_GameDataWidget.h"
#include "SG_GameModeBase.h"
#include "SG_PlayerState.h"

int32 USG_GameDataWidget::GetRoundSecondsRemaining() const
{
    const ASG_GameModeBase* GameMode = GetGameMode();
    return GameMode ? GameMode->GetRoundCountDown() : 0;
}

int32 USG_GameDataWidget::GetTotalRoundsNum() const
{
    const ASG_GameModeBase* GameMode = GetGameMode();
    return GameMode ? GameMode->GetTotalRoundsNum() : 0;
}

int32 USG_GameDataWidget::GetCurrentRoundNum() const
{
    const ASG_GameModeBase* GameMode = GetGameMode();
    return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 USG_GameDataWidget::GetPlayerKillsNum() const
{
    const ASG_PlayerState* PlayerState = GetPlayerState();
    return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 USG_GameDataWidget::GetPlayerDeathsNum() const
{
    const ASG_PlayerState* PlayerState = GetPlayerState();
    return PlayerState ? PlayerState->GetDeathsNum() : 0;
}
 
inline  ASG_GameModeBase* USG_GameDataWidget::GetGameMode() const
{
    return GetWorld() ?  Cast<ASG_GameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

FORCEINLINE ASG_PlayerState* USG_GameDataWidget::GetPlayerState() const
{
    return Cast<ASG_PlayerState>(GetOwningPlayerState());
}
