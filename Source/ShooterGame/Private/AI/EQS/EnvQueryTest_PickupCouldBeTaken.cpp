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
    UObject* DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);
    bool bWantsBeTakable = BoolValue.GetValue();

    for(FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());
        const auto Pickup = Cast<ABasePickup>(ItemActor);
        if(!Pickup) continue;

        const bool bCouldBeTaken = Pickup->CouldBeTaken();
        It.SetScore(TestPurpose, FilterType, bCouldBeTaken, bWantsBeTakable);
    }
}
