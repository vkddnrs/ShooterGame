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

bool UPlayerHUD_Widget::GetCurrentWeaponUIData(FWeaponUIData& WeaponUIData) const
{
    const auto WeaponComponent = GetWeaponComponent();
    if(!ensure(WeaponComponent)) return false;
    return WeaponComponent->GetCurrentWeaponUIData(WeaponUIData);
}

bool UPlayerHUD_Widget::GetCurrentWeaponAmmoData(FAmmoData& WeaponAmmoData) const
{
    const auto WeaponComponent = GetWeaponComponent();
    if(!ensure(WeaponComponent)) return false;
    return WeaponComponent->GetCurrentWeaponAmmoData(WeaponAmmoData);
}

UWeaponComponent* UPlayerHUD_Widget::GetWeaponComponent() const
{
    const auto Player = GetOwningPlayerPawn();
    if(!ensure(Player)) return nullptr;

    return Cast<UWeaponComponent>(Player->GetComponentByClass(UWeaponComponent::StaticClass()));
}
