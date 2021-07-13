// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SG_CoreTypes.h"
#include "GameHUD.generated.h"

class USG_BaseWidget;

UCLASS()
class SHOOTERGAME_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
    virtual void DrawHUD() override;

    protected:
    UPROPERTY(EditDefaultsOnly, Category = UI)
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = UI)
    TSubclassOf<UUserWidget> PauseWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = UI)
    TSubclassOf<UUserWidget> GameOverWidgetClass;

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TMap<ESG_MatchState, USG_BaseWidget*> GameWidgets;

    UPROPERTY()
    USG_BaseWidget* CurrentWidget = nullptr;

    void DrowCrossHair();
    void OnMathStateChanged(ESG_MatchState State);
	
};
