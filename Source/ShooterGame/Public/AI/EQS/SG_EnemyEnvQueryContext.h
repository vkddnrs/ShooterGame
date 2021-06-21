// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "SG_EnemyEnvQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API USG_EnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()

public:
     virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
     FName EnemyActorKeyName = "EnemyActor";
};
