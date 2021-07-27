// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SG_CharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API USG_CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
    virtual float GetMaxSpeed() const override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement, meta = (ClampMin = "1.0", ClampMax = "10.0"))
    float RunModefier = 2.f;

    // The time after which the falling character will be killed.
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement, meta = (ClampMin = "1.0", ClampMax = "10.0"))
    float TimeFallingOnDeath = 5.f;

protected:
    FTimerHandle TimerFalling;

    virtual void StartFalling(int32 Iterations, float remainingTime, float timeTick, const FVector& Delta, const FVector& subLoc) override;
    void OnTimeDeath();
};
