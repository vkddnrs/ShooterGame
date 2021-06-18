// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SG_FindEnemyService.generated.h"

class UBlackboardComponent;
class USG_AIPerceptionComponent;
class AIController;

UCLASS()
class SHOOTERGAME_API USG_FindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
    USG_FindEnemyService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
    
};
