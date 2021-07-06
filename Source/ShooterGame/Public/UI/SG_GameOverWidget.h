// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SGCoreTypes.h"
#include "SG_GameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SHOOTERGAME_API USG_GameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(meta = (BindWinget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(meta = (BindWinget))
    UButton* ResetLevelButton;


    UPROPERTY(EditDefaultsOnly, Category = UI)
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

private:
    void OnMatchStateChanged(ESG_MatchState State);
    void UpdatePlayersStat();

    UFUNCTION()
    void OnResetLevel();
};
