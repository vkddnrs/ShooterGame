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

    virtual void BeginPlay() override;

private:
    void DrowCrossHair();
    void OnMathStateChanged(ESG_MathState State);
	
};
