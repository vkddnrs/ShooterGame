// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SGCoreTypes.h"
#include "PlayerHUD_Widget.generated.h"

class UProgressBar;

UCLASS()
class SHOOTERGAME_API UPlayerHUD_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = UI)
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = UI)
    bool GetCurrentWeaponUIData(FWeaponUIData& WeaponUIData) const;

    UFUNCTION(BlueprintCallable, Category = UI)
    bool GetCurrentWeaponAmmoData(FAmmoData& WeaponAmmoData) const;

    UFUNCTION(BlueprintCallable, Category = UI)
    bool IsPlayerAlive() const;

    UFUNCTION(BlueprintCallable, Category = UI)
    bool IsPlayerSpectating() const;

    UFUNCTION(BlueprintImplementableEvent, Category = UI)
    void OnTakeDamage();

    UFUNCTION(BlueprintCallable, Category = UI)
    FString FormatsBullet(int32 BulletsNum) const;

    virtual bool Initialize() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthProgressBar;

    UPROPERTY(EditDefaultsOnly, Category = UI)
    float PercentBadColorThreshold = 0.3;

    UPROPERTY(EditDefaultsOnly, Category = UI)
    FLinearColor GoodColor = FLinearColor::Green;

    UPROPERTY(EditDefaultsOnly, Category = UI)
    FLinearColor BadColor = FLinearColor::Red;

private:
    void OnHealthChanged(float Health, float DeltaHealth);
    void OnNewPawn(APawn* NewPawn);
    void UpdateHealthBar();
	
};


