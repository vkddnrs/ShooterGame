// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickupCouldBeTaken.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UEnvQueryTest_PickupCouldBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()

public:
    UEnvQueryTest_PickupCouldBeTaken(const FObjectInitializer& Initializer);
    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;	
};
