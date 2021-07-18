// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SG_CoreTypes.h"
#include "SG_GameInstance.generated.h"



UCLASS()
class SHOOTERGAME_API USG_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    FLevelData GetStartupLevel() const { return StartupLevel; }
    void SetStartupLevel(const FLevelData& Data) { StartupLevel = Data; }

    TArray<FLevelData> GetLevelsData() const { return LevelsData; } // TODO  return const reference

    void ToggleVolume();

    inline FName GetMainMenuLevelName() const { return MainMenuLevelName; }

protected:
    UPROPERTY(EditDefaultsOnly, Category = Game, meta = (ToolTip = "Levels ID must be unique!"))
    TArray<FLevelData> LevelsData;

    UPROPERTY(EditDefaultsOnly, Category = Game)
    FName MainMenuLevelName = NAME_None;

     UPROPERTY(EditDefaultsOnly, Category = Sound)
    USoundClass* MasterSoundClass;


private:
    FLevelData StartupLevel;

};
