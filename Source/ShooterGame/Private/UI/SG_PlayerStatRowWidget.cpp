// ShooterGame. All Right Reserved.


#include "UI/SG_PlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void USG_PlayerStatRowWidget::SetPlayerName(const FText& Text)
{
    if(!PlayerNameTextBlock) return;
    PlayerNameTextBlock->SetText(Text);
}

void USG_PlayerStatRowWidget::SetKills(const FText& Text)
{
    if(!KillsTextBlock) return;
    KillsTextBlock->SetText(Text);
}

void USG_PlayerStatRowWidget::SetDeaths(const FText& Text)
{
    if(!DeathsTextBlock) return;
    DeathsTextBlock->SetText(Text);
}

void USG_PlayerStatRowWidget::SetTeam(const FText& Text)
{
    if(!TeamTextBlock) return;
    TeamTextBlock->SetText(Text);
}

void USG_PlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
    if(!PlayerIndicatorImage) return;
    PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
