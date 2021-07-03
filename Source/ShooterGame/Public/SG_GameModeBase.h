// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGCoreTypes.h"
#include "SG_GameModeBase.generated.h"

class AAIController;

UCLASS()
class SHOOTERGAME_API ASG_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
    ASG_GameModeBase();

    FOnMatchStateChangedSignature OnMatchStateChanged;

    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;
    virtual bool ClearPause() override;

    //Called by method UHealthComponent::Killed() of killed character.
    void Killed(AController* KillerController, AController* VictimController);
    
    void RespawnRequest(AController* Controller); // Call the method USG_RespawnComponent::Respawn() when the character dies.

    inline int32 GetRoundTime() const { return GameData.RoundTime; }
    inline int32 GetRoundCountDown() const { return RoundCountDown; }
    inline int32 GetTotalRoundsNum() const { return GameData.RoundsNum; }
    inline int32 GetCurrentRoundNum() const { return CurrentRound; }

protected:
    UPROPERTY(EditDefaultsOnly, Category = Game)
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = Game)
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, Category = Game)
    FGameData GameData;

private:
    ESG_MatchState MathState = ESG_MatchState::WaitingToStart;
    int32 CurrentRound = 1;
    int32 RoundCountDown = 0;
    FTimerHandle GameRoundTimerHandle;

    void SpawnBots();
    void StartRound();
    void GameTimerUpdate();

    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

    void CreateTeamsfInfo(); // Distribution of players by teams.
    FLinearColor DetermineColorByTeamID(int32 TeamID) const;
    void SetPlayerColor(AController* Controller);

    void StartRespawn(AController* Controller);

    void LogPlayersInfo();
    void GameOver();

    void SetMathState(ESG_MatchState State);
};
