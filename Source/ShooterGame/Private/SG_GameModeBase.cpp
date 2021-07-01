// ShooterGame. All Right Reserved.


#include "SG_GameModeBase.h"
#include "SG_PlayerController.h"
#include "SG_BaseCharacter.h"
#include "UI/GameHUD.h"
#include "AIController.h"
#include "SG_PlayerState.h"
#include "Components/SG_RespawnComponent.h"
#include "EngineUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogSGGameModeBase, All, All)

ASG_GameModeBase::ASG_GameModeBase()
{
    // override of defold propertys
    DefaultPawnClass = ASG_BaseCharacter::StaticClass();
    PlayerControllerClass = ASG_PlayerController::StaticClass();
    HUDClass = AGameHUD::StaticClass();
    PlayerStateClass = ASG_PlayerState::StaticClass();
}

void ASG_GameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();
    CreateTeamsfInfo();
    CurrentRound = 1;
    StartRound();

    SetMathState(ESG_MathState::InProgress);
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

void ASG_GameModeBase::Killed(AController* KillerController, AController* VictimController) 
{
    const auto KillerPlayerState = KillerController ? Cast<ASG_PlayerState>(KillerController->PlayerState) : nullptr;
    const auto VictimPlayerState = VictimController ? Cast<ASG_PlayerState>(VictimController->PlayerState) : nullptr;

    if(KillerPlayerState)
    {
        KillerPlayerState->AddKill();
    }

    if(VictimController)
    {
        VictimPlayerState->AddDeath();
    }

    StartRespawn(VictimController);
}

void ASG_GameModeBase::RespawnRequest(AController* Controller)
{
    ResetOnePlayer(Controller);
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
            ResetPlayers();
            StartRound();
        }
        else
        {
            GameOver();
        }
    }
}

void ASG_GameModeBase::ResetPlayers()
{
    if(!GetWorld()) return;

    for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void ASG_GameModeBase::ResetOnePlayer(AController* Controller)
{
    if(Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }

    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void ASG_GameModeBase::CreateTeamsfInfo()
{
    if(!GetWorld()) return;

    int32 TeamID = 1;
    for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if(!Controller) continue;

        const auto PlayerState = Cast<ASG_PlayerState>(Controller->PlayerState);
        PlayerState->SetTeamID(TeamID);
        PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
        SetPlayerColor(Controller);
        TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor ASG_GameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
    if(TeamID - 1 < GameData.TeamColors.Num()) // Default TeamID = 1
    {
        return GameData.TeamColors[TeamID - 1];
    }
    UE_LOG(LogSGGameModeBase, Warning, TEXT("No color for team id: %i, set to default %s"), TeamID, *GameData.DefaultTeamColor.ToString())
    return GameData.DefaultTeamColor;
}

void ASG_GameModeBase::SetPlayerColor(AController* Controller)
{
    if(!Controller) return;

    const auto Character = Cast<ASG_BaseCharacter>(Controller->GetPawn());
    if(!Character) return;

    const auto PlayerState = Cast<ASG_PlayerState>(Controller->PlayerState);
    if(!PlayerState) return;
    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ASG_GameModeBase::StartRespawn(AController* Controller)
{
    const bool RespawnEvalable = RoundCountDown > GameData.MinRemainRoundTimeForRespawn + GameData.RespawnTime;
    if(!RespawnEvalable) return;

    const auto RespawnComponent = Controller->FindComponentByClass <USG_RespawnComponent>();
    if(!RespawnComponent) return;

    RespawnComponent->Respawn(GameData.RespawnTime);
}

void ASG_GameModeBase::LogPlayersInfo()
{
    if(!GetWorld()) return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if(!Controller) continue;

        const auto PlayerState = Cast<ASG_PlayerState>(Controller->PlayerState);
        if(!PlayerState) continue;

        PlayerState->LogInfo();
    }
}

void ASG_GameModeBase::GameOver()
{
    UE_LOG(LogSGGameModeBase, Display, TEXT("************* GAME OVER **************"))
    LogPlayersInfo();

    for(auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if(Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }
    SetMathState(ESG_MathState::GameOver);
}

void ASG_GameModeBase::SetMathState(ESG_MathState State)
{
    if(MathState == State) return;

    MathState = State;
    OnMathStateChanged.Broadcast(MathState);
}
