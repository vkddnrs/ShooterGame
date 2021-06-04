// ShooterGame. All Right Reserved.


#include "UI/PlayerHUD_Widget.h"
#include "Components/HealthComponent.h"
#include "Components/WeaponComponent.h"
#include "Components/HealthComponent.h"

float UPlayerHUD_Widget::GetHealthPercent() const
{
    const auto HealthComponent = GetHealthComponent();
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

bool UPlayerHUD_Widget::IsPlayerAlive() const
{
    const auto HealthComponent = GetHealthComponent();
    return HealthComponent && !HealthComponent->IsDead();
}

bool UPlayerHUD_Widget::IsPlayerSpectating() const
{
    const APlayerController* Controller = GetOwningPlayer();
    return Controller->GetStateName() == NAME_Spectating;
}

UWeaponComponent* UPlayerHUD_Widget::GetWeaponComponent() const
{
    const auto Player = GetOwningPlayerPawn();
    if(!ensure(Player)) return nullptr;

    return Cast<UWeaponComponent>(Player->GetComponentByClass(UWeaponComponent::StaticClass()));
}

UHealthComponent* UPlayerHUD_Widget::GetHealthComponent() const
{
    const auto Player = GetOwningPlayerPawn();
    if(!ensure(Player)) return nullptr;

    return Cast<UHealthComponent>(Player->GetComponentByClass(UHealthComponent::StaticClass()));
}
