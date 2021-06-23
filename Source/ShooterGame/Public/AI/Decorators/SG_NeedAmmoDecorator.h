// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SG_NeedAmmoDecorator.generated.h"

class ASG_BaseWeapon;

UCLASS()
class SHOOTERGAME_API USG_NeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
    USG_NeedAmmoDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
    TSubclassOf<ASG_BaseWeapon> WeaponType;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
