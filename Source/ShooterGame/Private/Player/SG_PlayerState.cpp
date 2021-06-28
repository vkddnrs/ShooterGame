// ShooterGame. All Right Reserved.


#include "Player/SG_PlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSG_PlayerState, All, All)

void ASG_PlayerState::LogInfo()
{
    UE_LOG(LogSG_PlayerState, Display, TEXT("TeamID: %i, KillsNum: %i, DeathsNum: %i"), TeamID, KillsNum, DeathsNum)
}
