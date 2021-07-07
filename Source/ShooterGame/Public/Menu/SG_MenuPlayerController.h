// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SG_MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API ASG_MenuPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
     virtual void BeginPlay() override;
};
