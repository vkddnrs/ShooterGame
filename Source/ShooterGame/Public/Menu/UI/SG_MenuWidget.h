// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_MenuWidget.generated.h"

class UButton;

UCLASS()
class SHOOTERGAME_API USG_MenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWinget))
    UButton* StartGameButton;

    UPROPERTY(meta = (BindWinget))
    UButton* QuitButton;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnStartGame();

    UFUNCTION()
    void OnQuitGame();
};
