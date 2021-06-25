// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGCoreTypes.h"
#include "SG_GameModeBase.generated.h"

class AAIController;

UCLASS()
class SHOOTERGAME_API ASG_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
    ASG_GameModeBase();

    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = Game)
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = Game)
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, Category = Game)
    FGameData GameData;

private:
    void SpawnBots();


};
