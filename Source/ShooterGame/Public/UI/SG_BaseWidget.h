// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_BaseWidget.generated.h"

class USoundCue;

UCLASS()
class SHOOTERGAME_API USG_BaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void Show();

protected:
    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ShowAnimation;

    UPROPERTY(EditDefaultsOnly, Category = Sound)
    USoundCue* OpenSound;
};
