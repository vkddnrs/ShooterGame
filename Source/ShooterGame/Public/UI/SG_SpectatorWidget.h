// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_SpectatorWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API USG_SpectatorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = UI)
    bool GetRespawnTime(int32& CountDownTime) const;
	
};
