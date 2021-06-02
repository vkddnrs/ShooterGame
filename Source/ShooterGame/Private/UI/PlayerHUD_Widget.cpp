// ShooterGame. All Right Reserved.


#include "UI/PlayerHUD_Widget.h"
#include "Components/HealthComponent.h"

float UPlayerHUD_Widget::GetHealthPercent() const
{
    const auto Player = GetOwningPlayerPawn();
    if(!ensure(Player)) return 0.0;

    const auto HealthComponent = Cast<UHealthComponent>( Player->GetComponentByClass(UHealthComponent::StaticClass()));
    if(!ensure(HealthComponent)) return 0.0;

    return HealthComponent->GetHealthPercent();
}
