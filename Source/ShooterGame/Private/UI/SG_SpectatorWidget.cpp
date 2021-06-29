// ShooterGame. All Right Reserved.


#include "UI/SG_SpectatorWidget.h"
#include "Components/SG_RespawnComponent.h"


bool USG_SpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
    const auto RespawnComponent = GetOwningPlayer()->FindComponentByClass<USG_RespawnComponent>();
    if(!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

    CountDownTime = RespawnComponent->GetRespawnCauntDown();
    return true;
}
