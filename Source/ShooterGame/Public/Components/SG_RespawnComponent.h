// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SG_RespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API USG_RespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USG_RespawnComponent();

    // Called from ASG_GameModeBase::RespawnRequest() when owned character dies.
    // Invoke RespawnTimer.
    void Respawn(int32 RespawnTime);
    inline  int32 GetRespawnCauntDown() const { return RespawnCauntDown; }
    bool IsRespawnInProgress() const;

private:
    FTimerHandle RespawnTimerHandle;
    int32 RespawnCauntDown = 0;

    void RespawnTimerUpdate();
};
