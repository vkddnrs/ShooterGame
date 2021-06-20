// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SG_ChangeWeaponService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API USG_ChangeWeaponService : public UBTService
{
	GENERATED_BODY()

public:
    USG_ChangeWeaponService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (ClampMin = 0.f, ClampMax = 1.f))
    float Probability = 0.8f;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
