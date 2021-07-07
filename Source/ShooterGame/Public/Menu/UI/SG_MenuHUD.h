// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SG_MenuHUD.generated.h"

/**
 * Creates a MainWidget and adds it to the Viewport.
 */
UCLASS()
class SHOOTERGAME_API ASG_MenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
    // main menu widget
    UPROPERTY(EditDefaultsOnly, Category = UI)
    TSubclassOf<UUserWidget> MenuWidgetClass;

    virtual void BeginPlay() override;
};
