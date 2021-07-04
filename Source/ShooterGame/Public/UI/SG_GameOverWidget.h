// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SGCoreTypes.h"
#include "SG_GameOverWidget.generated.h"

class UVerticalBox;

UCLASS()
class SHOOTERGAME_API USG_GameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual bool Initialize() override;

protected:
    UPROPERTY(meta = (BindWinget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, Category = UI)
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

private:
    void OnMatchStateChanged(ESG_MatchState State);
    void UpdatePlayersStat();
};
