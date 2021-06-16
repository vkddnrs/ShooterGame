// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NextLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UNextLocationTask();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    float Radius = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    FBlackboardKeySelector AimLocationKey;
      
};
