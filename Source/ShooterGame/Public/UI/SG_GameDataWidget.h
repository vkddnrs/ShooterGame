// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_GameDataWidget.generated.h"

class ASG_GameModeBase;
class ASG_PlayerState;

UCLASS()
class SHOOTERGAME_API USG_GameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = GameData)
    int32 GetRoundSecondsRemaining() const;

    UFUNCTION(BlueprintCallable, Category = GameData)
    int32 GetCurrentRoundNum() const;

    UFUNCTION(BlueprintCallable, Category = GameData)
    int32 GetTotalRoundsNum() const;

    UFUNCTION(BlueprintCallable, Category = GameData)
    int32 GetPlayerKillsNum() const;

    UFUNCTION(BlueprintCallable, Category = GameData)
    int32 GetPlayerDeathsNum() const;

private:
    ASG_GameModeBase* GetGameMode() const;
    ASG_PlayerState* GetPlayerState() const;
};
