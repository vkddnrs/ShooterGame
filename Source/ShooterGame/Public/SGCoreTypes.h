#pragma once

#include "SGCoreTypes.generated.h"

class ASG_BaseWeapon;

    // weapon

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, ASG_BaseWeapon*)

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
    int32 Bullets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon, meta = (EditCondition = "!bInfinite"))
    int32 Clips;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
    bool bInfinite = false;
};

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category = Weapon)
    TSubclassOf<ASG_BaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = Weapon)
    UAnimMontage* ReloadAnimMontage;
};

// UI

USTRUCT(BlueprintType)
struct FWeaponUIData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
    UTexture2D* MainIcon;

    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = UI)
    UTexture2D* CrossHairIcon;
};


// health

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, float);

// VFX

class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FDecalData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category = VFX)
    UMaterialInterface* Material;

    UPROPERTY(EditDefaultsOnly, Category = VFX)
    FVector Size = FVector(10.f);

    UPROPERTY(EditDefaultsOnly, Category = VFX)
    float LifeTime = 5.f;

    UPROPERTY(EditDefaultsOnly, Category = VFX)
    float FadeOutTime = 0.7f;
};

USTRUCT(BlueprintType) struct FImpactData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category = VFX)
    // ReSharper disable once UnrealHeaderToolParserError
    UNiagaraSystem* NiagaraEffect;

    UPROPERTY(EditDefaultsOnly, Category = VFX)
    FDecalData DecalData;
};

USTRUCT(BlueprintType) struct FGameData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, Category = Game, meta = (ClampMin = 1, ClampMax = 100))
    int32 PlayersNum = 2;

    UPROPERTY(EditDefaultsOnly, Category = Game, meta = (ClampMin = 1, ClampMax = 10))
    int32 RoundsNum = 4;

    UPROPERTY(EditDefaultsOnly, Category = Game, meta = (ClampMin = 3, ClampMax = 300))
    int32 RoundTime = 10; // in seconds

    UPROPERTY(EditDefaultsOnly, Category = Game)
    FLinearColor DefaultTeamColor = FLinearColor::Blue;

    // Available colors for teams.
    UPROPERTY(EditDefaultsOnly, Category = Game)
    TArray<FLinearColor> TeamColors;

    UPROPERTY(EditDefaultsOnly, Category = Game, meta = (ClampMin = 3, ClampMax = 20))
    int32 RespawnTime = 5;  // in seconds

    UPROPERTY(EditDefaultsOnly, Category = Game, meta = (ClampMin = 5, ClampMax = 200))
    int32 MinRemainRoundTimeForRespawn = 10;  // in seconds
};


UENUM(BlueprintType)
enum class ESG_MatchState : uint8
{
    WaitingToStart = 0,
    InProgress,
    Pause,
    GameOver
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, ESG_MatchState);