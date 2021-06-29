// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SG_PlayerController.generated.h"


UCLASS()
class SHOOTERGAME_API ASG_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    ASG_PlayerController();

protected:
    UPROPERTY(VisibleAnywhere, Category = Components)
    class USG_RespawnComponent* RespawnComponent;

	
};
