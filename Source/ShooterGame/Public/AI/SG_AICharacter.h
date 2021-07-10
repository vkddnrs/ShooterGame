// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/SG_BaseCharacter.h"
#include "SG_AICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class SHOOTERGAME_API ASG_AICharacter : public ASG_BaseCharacter
{
    GENERATED_BODY()

public:
    ASG_AICharacter(const FObjectInitializer& ObjInit);

    UPROPERTY(EditDefaultsOnly, Category = AI)
    UBehaviorTree* BehaviorTreeAsset;

    UPROPERTY(EditDefaultsOnly, Category = AI)
    float HealthWidgetVisibilityDistance = 3000.f;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
    UWidgetComponent* HealthWidgetComponent;

    virtual void BeginPlay() override;
    virtual void OnDeath() override;
    virtual void OnHealthChanged(float Health, float DeltaHealth) override;

private:
    FTimerHandle HealthWidgetVisibilityTimerHandle;
    void UpdateHealthWidgetVisibility();
};
