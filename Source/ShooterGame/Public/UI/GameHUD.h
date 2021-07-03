// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SGCoreTypes.h"
#include "GameHUD.generated.h"

/**
 * 
 */
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

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TMap<ESG_MathState, UUserWidget*> GameWidgets;

    UPROPERTY()
    UUserWidget* CurrentWidget = nullptr;

    void DrowCrossHair();
    void OnMathStateChanged(ESG_MathState State);
	
};
