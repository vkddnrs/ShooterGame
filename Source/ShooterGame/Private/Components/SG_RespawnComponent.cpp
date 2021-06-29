// ShooterGame. All Right Reserved.


#include "Components/SG_RespawnComponent.h"
#include "SG_GameModeBase.h"

USG_RespawnComponent::USG_RespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USG_RespawnComponent::Respawn(int32 RespawnTime)
{
    if(!GetWorld()) return;

    RespawnCauntDown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USG_RespawnComponent::RespawnTimerUpdate, 1.f, true);
}

inline bool USG_RespawnComponent::IsRespawnInProgress() const
{
    return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void USG_RespawnComponent::RespawnTimerUpdate()
{
    if(--RespawnCauntDown == 0)
    {
        if(!GetWorld()) return;
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

        const auto GameMode = Cast<ASG_GameModeBase>(GetWorld()->GetAuthGameMode());
        if(!GameMode) return;
        GameMode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}




