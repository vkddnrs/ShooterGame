// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
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

private:
    void DrowCrossHair();

	
};
