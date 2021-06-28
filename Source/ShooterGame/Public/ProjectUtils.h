#pragma once
#include "SG_PlayerState.h"

class APawn;

DEFINE_LOG_CATEGORY_STATIC(LogProjectUtils, All, All)

class ProjectUtils
{
public:
    template<typename T>
    static T* GetPlayerComponent(APawn* PlayerPawn)
    {
        if(!PlayerPawn) return nullptr;
        return Cast<T>(PlayerPawn->GetComponentByClass(T::StaticClass()));
    }

    static bool AreEnemies(AController* Controller_1, AController* Controller_2)
    {
        if(!Controller_1 || !Controller_2 || Controller_1 == Controller_2) return false;

        const auto PlayerState_1 = Cast<ASG_PlayerState>(Controller_1->PlayerState);
        const auto PlayerState_2 = Cast<ASG_PlayerState>(Controller_2->PlayerState);

        return PlayerState_1 && PlayerState_2 && PlayerState_1->GetTeamID() != PlayerState_2->GetTeamID();
    }
};