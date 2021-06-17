// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SG_AIController.generated.h"

class USG_AIPerceptionComponent;

UCLASS()
class SHOOTERGAME_API ASG_AIController : public AAIController
{
	GENERATED_BODY()

public:
    ASG_AIController();

protected:
    UPROPERTY(VisibleAnywhere, Category = Components)
    USG_AIPerceptionComponent* SG_AIPerceptionComponent;

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaSeconds) override;

};
