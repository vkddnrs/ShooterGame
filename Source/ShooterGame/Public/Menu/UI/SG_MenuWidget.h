// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SGCoreTypes.h"
#include "SG_MenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USG_GameInstance;
class USG_LevelItemWidget;

UCLASS()
class SHOOTERGAME_API USG_MenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWinget))
    UButton* StartGameButton;

    UPROPERTY(meta = (BindWinget))
    UButton* QuitButton;

    UPROPERTY(meta = (BindWinget))
    UHorizontalBox* LevelItemsBox;

    UPROPERTY(EditDefaultsOnly, Category = UI)
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

    virtual void NativeOnInitialized() override;

private:
    // List of Level Item Widgets
    TArray<USG_LevelItemWidget*> LevelItemWidgets;

    UFUNCTION()
    void OnStartGame();

    UFUNCTION()
    void OnQuitGame();

    void InitLevelItems();
    void OnLevelSelected(const FLevelData& Data);
    USG_GameInstance* GetSGGameInstance() const;
};
