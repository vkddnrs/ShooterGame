// ShooterGame. All Right Reserved.


#include "Menu/UI/SG_MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SG_GameInstance.h"
#include "Components/HorizontalBox.h"
#include "Menu/UI/SG_LevelItemWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogSG_MenuWidget, All, All)

void USG_MenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USG_MenuWidget::OnStartGame);
    }

    if(QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &USG_MenuWidget::OnQuitGame);
    }

    InitLevelItems();
}

void USG_MenuWidget::InitLevelItems()
{
    if(!GetWorld()) return;

    const auto SGGameInstance = GetSGGameInstance();
    if(!SGGameInstance) return;

    checkf(SGGameInstance->GetLevelsData().Num() != 0, TEXT("Error: Levels data is empty!"))

    if(!LevelItemsBox) return;
    LevelItemsBox->ClearChildren();

    for (auto LevelData : SGGameInstance->GetLevelsData())
    {
        const auto LevelItemWidget = CreateWidget<USG_LevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if(!LevelItemWidget) continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &USG_MenuWidget::OnLevelSelected);

        LevelItemsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }

    if(SGGameInstance->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(SGGameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(SGGameInstance->GetStartupLevel());
    }
}

void USG_MenuWidget::OnStartGame()
{
    if(!GetWorld()) return;

    const auto SGGameInstance = GetSGGameInstance();
    if(!SGGameInstance) return;

    UGameplayStatics::OpenLevel(this, SGGameInstance->GetStartupLevel().LevelName);
}

void USG_MenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USG_MenuWidget::OnLevelSelected(const FLevelData& Data)
{
    const auto SGGameInstance = GetSGGameInstance();
    if(!SGGameInstance) return;

    SGGameInstance->SetStartupLevel(Data);

    // for selected level we set FrameLevel on visible
    for(auto LevelItemWidget : LevelItemWidgets)
    {
        if(LevelItemWidget)
        {
            const bool IsSelected = LevelItemWidget->GetLevelData().LevelID == Data.LevelID;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}

USG_GameInstance* USG_MenuWidget::GetSGGameInstance() const
{
    return Cast<USG_GameInstance>(GetGameInstance());
}
