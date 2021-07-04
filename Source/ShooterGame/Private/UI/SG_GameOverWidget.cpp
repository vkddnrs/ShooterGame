// ShooterGame. All Right Reserved.


#include "UI/SG_GameOverWidget.h"
#include "SG_GameModeBase.h"
#include "Player/SG_PlayerState.h"
#include "SG_PlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "ProjectUtils.h"


bool USG_GameOverWidget::Initialize()
{
    if(GetWorld())
    {
        const auto GameMode = Cast<ASG_GameModeBase>(GetWorld()->GetAuthGameMode());
        if(GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &USG_GameOverWidget::OnMatchStateChanged);
        }
    }

    return Super::Initialize();
}

void USG_GameOverWidget::OnMatchStateChanged(ESG_MatchState State)
{
    if(State == ESG_MatchState::GameOver)
    {
        UpdatePlayersStat();
    }
}

void USG_GameOverWidget::UpdatePlayersStat()
{
    if(!GetWorld() || !PlayerStatBox) return;

    PlayerStatBox->ClearChildren(); 

    for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if(!Controller) continue;        

        const auto PlayerState = Cast<ASG_PlayerState>(Controller->PlayerState);
        if(!PlayerState) continue;

        const auto PlayerStatRowWidget = CreateWidget<USG_PlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
        if(!PlayerStatRowWidget) continue;

        PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStatRowWidget->SetKills(ProjectUtils::TextFromInt(PlayerState->GetKillsNum()));
        PlayerStatRowWidget->SetDeaths(ProjectUtils::TextFromInt(PlayerState->GetDeathsNum()));
        PlayerStatRowWidget->SetTeam(ProjectUtils::TextFromInt(PlayerState->GetTeamID()));
        PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

        PlayerStatBox->AddChild(PlayerStatRowWidget);
    }    
}
