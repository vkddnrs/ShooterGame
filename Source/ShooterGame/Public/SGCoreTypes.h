#pragma once

#include "SGCoreTypes.generated.h"

class ASG_BaseWeapon;
    // weapon

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature)

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    int32 Bullets;

    UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "!bInfinite"))
    int32 Clips;

    UPROPERTY(EditDefaultsOnly)
    bool bInfinite = false;
};

USTRUCT()
struct FWeaponData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ASG_BaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly)
    UAnimMontage* ReloadAnimMontage;
};

// health

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);