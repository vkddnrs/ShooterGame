// ShooterGame. All Right Reserved.


#include "UI/PlayerHUD_Widget.h"
#include "Components/HealthComponent.h"
#include "Components/WeaponComponent.h"

float UPlayerHUD_Widget::GetHealthPercent() const
{
    const auto Player = GetOwningPlayerPawn();
    if(!ensure(Player)) return 0.0;

    const auto HealthComponent = Cast<UHealthComponent>( Player->GetComponentByClass(UHealthComponent::StaticClass()));
    if(!ensure(HealthComponent)) return 0.0;

    return HealthComponent->GetHealthPercent();
}

bool UPlayerHUD_Widget::GetWeaponUIData(FWeaponUIData& WeaponUIData) const
{
    const auto Player = GetOwningPlayerPawn();
    if(!ensure(Player)) return 0.0;

    const auto WeaponComponent = Cast<UWeaponComponent>(Player->GetComponentByClass(UWeaponComponent::StaticClass()));
    if(!ensure(WeaponComponent)) return false;

    return WeaponComponent->GetWeaponUIData(WeaponUIData);
}
