// ShooterGame. All Right Reserved.


#include "SG_PlayerController.h"
#include "Components/SG_RespawnComponent.h"
#include "SG_GameModeBase.h"
#include "SG_GameInstance.h"

ASG_PlayerController::ASG_PlayerController()
{
    RespawnComponent = CreateDefaultSubobject<USG_RespawnComponent>("RespawnComponent");
}

void ASG_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    if(GetWorld()) 
    {
        if(const auto GameMode = Cast<ASG_GameModeBase>(GetWorld()->GetAuthGameMode()))
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASG_PlayerController::OnMathStateChanged);
        }
    }
}

void ASG_PlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    OnNewPawn.Broadcast(InPawn); // in case of a possible bug, when this method will not be called in the base class
}

void ASG_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if(!InputComponent) return;

    InputComponent->BindAction("PauseGame", EInputEvent::IE_Pressed, this, &ASG_PlayerController::OnPauseGame);
    InputComponent->BindAction("Mute", EInputEvent::IE_Pressed, this, &ASG_PlayerController::OnMuteSound);

}

void ASG_PlayerController::BeginSpectatingState()
{
    Super::BeginSpectatingState();

    ServerViewNextPlayer();
    ServerViewNextPlayer();
}

void ASG_PlayerController::OnPauseGame()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode())  return;

    GetWorld()->GetAuthGameMode()->SetPause(this);

}

void ASG_PlayerController::OnMathStateChanged(ESG_MatchState MathState)
{
    if(MathState == ESG_MatchState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

void ASG_PlayerController::OnMuteSound()
{
    if(!GetWorld()) return;

    const auto GameInstance = GetWorld()->GetGameInstance<USG_GameInstance>();
    if(!GameInstance)return;

    GameInstance->ToggleVolume();
}
