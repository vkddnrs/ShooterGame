// ShooterGame. All Right Reserved.


#include "SG_GameModeBase.h"
#include "SG_PlayerController.h"
#include "SG_BaseCharacter.h"
#include "UI/GameHUD.h"
#include "AIController.h"

DEFINE_LOG_CATEGORY_STATIC(LogSGGameModeBase, All, All)

ASG_GameModeBase::ASG_GameModeBase()
{
    // override of defold propertys
    DefaultPawnClass = ASG_BaseCharacter::StaticClass();
    PlayerControllerClass = ASG_PlayerController::StaticClass();
    HUDClass = AGameHUD::StaticClass();
}

void ASG_GameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();
    CurrentRound = 1;
    StartRound();
}

UClass* ASG_GameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if(InController && InController->IsA<AAIController>())
    {
        if(AIPawnClass) 
        {
            return AIPawnClass;
        }        
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASG_GameModeBase::SpawnBots()
{
    if(!ensure(GetWorld() || AIControllerClass)) return;

    // we take into account our Player character
    for(int32 i = 0; i < GameData.PlayersNum - 1; i++)
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto SG_AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnParameters);
        RestartPlayer(SG_AIController);
    }
}

void ASG_GameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASG_GameModeBase::GameTimerUpdate, 1.f, true);
}

void ASG_GameModeBase::GameTimerUpdate()
{
    UE_LOG(LogSGGameModeBase, Display, TEXT("Time: %i / Round %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum)

    // in the case when you need to know the frequency of the timer.
    // const auto TimerRate = GetWorldTimerManager().GetTimerRate(GameRoundTimerHandle);
    // RoundCountDown -= TimerRate;

    if(--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

        if(CurrentRound + 1 <= GameData.RoundsNum)
        {
            CurrentRound++;
            StartRound();
        }
        else
        {
            UE_LOG(LogSGGameModeBase, Display, TEXT("********************** GAME OVER ************************"))
        }

    }
}
