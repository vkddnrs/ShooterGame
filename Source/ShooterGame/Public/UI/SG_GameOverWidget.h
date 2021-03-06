// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SG_BaseWidget.h"
#include "SG_CoreTypes.h"
#include "SG_GameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SHOOTERGAME_API USG_GameOverWidget : public USG_BaseWidget
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
