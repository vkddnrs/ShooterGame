// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SG_HealtnPercentDecorator.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API USG_HealtnPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
    USG_HealtnPercentDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    float HealthPercentThreshold = 0.6f;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;	
};
