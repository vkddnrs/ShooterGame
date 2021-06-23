// ShooterGame. All Right Reserved.


#include "AI/EQS/EnvQueryTest_PickupCouldBeTaken.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/BasePickup.h"

UEnvQueryTest_PickupCouldBeTaken::UEnvQueryTest_PickupCouldBeTaken(const FObjectInitializer& Initializer) : Super(Initializer)
{
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PickupCouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
    for(FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());
        const auto Pickup = Cast<ABasePickup>(ItemActor);
        if(!Pickup) continue;
     
        if(Pickup->CouldBeTaken())
        {
            It.SetScore(TestPurpose, FilterType, true, true);
        }
        else
        {
            It.ForceItemState(EEnvItemStatus::Failed);
        }
    }
}
