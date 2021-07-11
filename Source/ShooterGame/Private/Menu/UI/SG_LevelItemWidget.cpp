// ShooterGame. All Right Reserved.


#include "Menu/UI/SG_LevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void USG_LevelItemWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(LevelSelectButton)
    {
        LevelSelectButton->OnClicked.AddDynamic(this, &USG_LevelItemWidget::OnLevelItemClicked);
        LevelSelectButton->OnHovered.AddDynamic(this, &USG_LevelItemWidget::OnLevelItemHovered);
        LevelSelectButton->OnUnhovered.AddDynamic(this, &USG_LevelItemWidget::OnLevelItemUnovered);
    }
}

void USG_LevelItemWidget::OnLevelItemClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}

void USG_LevelItemWidget::OnLevelItemHovered()
{
    if(FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Visible);
    }
}

void USG_LevelItemWidget::OnLevelItemUnovered()
{
    if(FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Hidden);
    }
}

void USG_LevelItemWidget::SetLevelData(const FLevelData& Data)
{
    LevelData = Data;

    if(LevelNameTextBlock)
    {
        LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
    }
    if(LevelImage)
    {
        LevelImage->SetBrushFromTexture(Data.LevelThumb);
    }
}

void USG_LevelItemWidget::SetSelected(bool IsSelected)
{
    if(LevelImage)
    {
        LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);
    }
}
