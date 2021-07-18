// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SG_CoreTypes.h"
#include "SG_PlayerController.generated.h"


UCLASS()
class SHOOTERGAME_API ASG_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    ASG_PlayerController();

protected:
    UPROPERTY(VisibleAnywhere, Category = Components)
    class USG_RespawnComponent* RespawnComponent;

    virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
    virtual void SetupInputComponent() override;

private:
    void OnPauseGame();
    void OnMathStateChanged(ESG_MatchState MathState);
    void OnMuteSound();
};
