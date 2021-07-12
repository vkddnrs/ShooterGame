// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SG_BaseWidget.h"
#include "SG_PauseWidget.generated.h"

class UButton;

UCLASS()
class SHOOTERGAME_API USG_PauseWidget : public USG_BaseWidget
{
	GENERATED_BODY()

public:
    virtual bool Initialize() override;

protected:
    UPROPERTY(meta = (BindWidget)) // Binding Variable whith the Button same name at widget.
    UButton* ClearPauseButton; 

private:
    UFUNCTION()
    void OnClearPause();

	
};
