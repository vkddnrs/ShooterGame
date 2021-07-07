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
    FString TestString = "Hello game!";
	
};
