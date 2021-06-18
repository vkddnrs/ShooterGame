// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SG_FireService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API USG_FireService : public UBTService
{
	GENERATED_BODY()

public:
    USG_FireService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;	    
	
};
