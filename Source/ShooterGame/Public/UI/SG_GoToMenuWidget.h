// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_GoToMenuWidget.generated.h"

class UButton;

UCLASS()
class SHOOTERGAME_API USG_GoToMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* GoToMenuButton;

private:
    UFUNCTION()
    void OnGoToMenu();
	
};
