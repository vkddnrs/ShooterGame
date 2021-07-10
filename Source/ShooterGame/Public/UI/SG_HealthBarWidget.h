// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_HealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class SHOOTERGAME_API USG_HealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void SetHealthPercent(float Percent);

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthProgressBar;

    UPROPERTY(EditDefaultsOnly, Category = UI)
    float PercentVisibilityThreshold = 0.8;

    UPROPERTY(EditDefaultsOnly, Category = UI)
    float PercentBadColorThreshold = 0.3;

    UPROPERTY(EditDefaultsOnly, Category = UI)
    FLinearColor GoodColor = FLinearColor::Green;

    UPROPERTY(EditDefaultsOnly, Category = UI)
    FLinearColor BadColor = FLinearColor::Red;
};
