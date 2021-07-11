// ShooterGame. All Right Reserved.


#include "UI/PlayerHUD_Widget.h"
#include "Components/HealthComponent.h"
#include "Components/WeaponComponent.h"
#include "ProjectUtils.h"
#include "Components/ProgressBar.h"


bool UPlayerHUD_Widget::Initialize()
{
    if(GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UPlayerHUD_Widget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }

    return Super::Initialize();
}

float UPlayerHUD_Widget::GetHealthPercent() const
{
    const auto HealthComponent = ProjectUtils::GetPlayerComponent<UHealthComponent>(GetOwningPlayerPawn());
    if(!HealthComponent) return 0.0;
    return HealthComponent->GetHealthPercent();
}

bool UPlayerHUD_Widget::GetCurrentWeaponUIData(FWeaponUIData& WeaponUIData) const
{
    const auto WeaponComponent = ProjectUtils::GetPlayerComponent<UWeaponComponent>(GetOwningPlayerPawn());
    if(!WeaponComponent) return false;
    return WeaponComponent->GetCurrentWeaponUIData(WeaponUIData);
}

bool UPlayerHUD_Widget::GetCurrentWeaponAmmoData(FAmmoData& WeaponAmmoData) const
{
    const auto WeaponComponent = ProjectUtils::GetPlayerComponent<UWeaponComponent>(GetOwningPlayerPawn());
    if(!WeaponComponent) return false;
    return WeaponComponent->GetCurrentWeaponAmmoData(WeaponAmmoData);
}

bool UPlayerHUD_Widget::IsPlayerAlive() const
{
    const auto HealthComponent = ProjectUtils::GetPlayerComponent<UHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}

bool UPlayerHUD_Widget::IsPlayerSpectating() const
{
    const APlayerController* Controller = GetOwningPlayer();
    return Controller->GetStateName() == NAME_Spectating;
}

void UPlayerHUD_Widget::OnHealthChanged(float Health, float DeltaHealth)
{
    if(DeltaHealth >= 0.f) return;

    OnTakeDamage();
    UpdateHealthBar();
}

void UPlayerHUD_Widget::OnNewPawn(APawn* NewPawn)
{
    const auto HealthComponent = ProjectUtils::GetPlayerComponent<UHealthComponent>(NewPawn);
    // in case of a possible bug when this method will be called more than once
    if(HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
    {
        UE_LOG(LogTemp, Display, TEXT("OnNewPawn() is called!!!"))
        HealthComponent->OnHealthChanged.AddUObject(this, &UPlayerHUD_Widget::OnHealthChanged);
    }
    UpdateHealthBar();
}

void UPlayerHUD_Widget::UpdateHealthBar()
{
    if(HealthProgressBar)
    {
        HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentBadColorThreshold ? GoodColor : BadColor);
    }
}

FString UPlayerHUD_Widget::FormatsBullet(int32 BulletsNum) const
{
    const int32 MaxLen = 2;
    const TCHAR PrefixSymbol = '0';

    FString BulletStr = FString::FromInt(BulletsNum);
    const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();

    if(SymbolsNumToAdd > 0)
    {
        BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
    }
    return BulletStr;
}
