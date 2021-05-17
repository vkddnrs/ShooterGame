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

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement, meta = (ClampMin = "1.5", ClampMax = "10.0"))
    float RunModefier = 2.f;
	
};
