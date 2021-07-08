// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SG_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API USG_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    inline FName GetStartupLevelName() const { return StartupLevelName; }
    inline FName GetMainMenuLevelName() const { return MainMenuLevelName; }

protected:
    UPROPERTY(EditDefaultsOnly, Category = Game)
    FName StartupLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = Game)
    FName MainMenuLevelName = NAME_None;	
};
