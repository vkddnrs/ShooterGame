// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SGCoreTypes.h"
#include "PlayerHUD_Widget.generated.h"

class UWeaponComponent;
/**
 * 
 */
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

private:
    UWeaponComponent* GetWeaponComponent() const;
	
};
