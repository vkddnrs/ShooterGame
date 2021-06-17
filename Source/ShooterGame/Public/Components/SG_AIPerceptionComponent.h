// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "SG_AIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API USG_AIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
    AActor* GetClosestEnemy() const;
	
};
