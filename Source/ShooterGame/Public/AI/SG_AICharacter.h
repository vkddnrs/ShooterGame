// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/SG_BaseCharacter.h"
#include "SG_AICharacter.generated.h"

class UBehaviorTree;
/**
 * 
 */
UCLASS()
class SHOOTERGAME_API ASG_AICharacter : public ASG_BaseCharacter
{
    GENERATED_BODY()

public:
    ASG_AICharacter(const FObjectInitializer& ObjInit);

    UPROPERTY(EditDefaultsOnly, Category = AI)
    UBehaviorTree* BehaviorTreeAsset;
};
