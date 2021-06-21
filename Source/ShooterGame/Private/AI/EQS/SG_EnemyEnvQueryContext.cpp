// ShooterGame. All Right Reserved.


#include "AI/EQS/SG_EnemyEnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
//#include "Blueprint/AIBlueprintHelperLibrary.h"

void USG_EnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
    const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
    UBlackboardComponent* Blackboard = nullptr;

    if(QueryOwner != nullptr)
    {
        APawn* TargetPawn = Cast<APawn>(QueryOwner);
        if(TargetPawn && TargetPawn->GetController())
        {
            Blackboard = TargetPawn->GetController()->FindComponentByClass<UBlackboardComponent>();
        }

        if(Blackboard == nullptr)
        {
            Blackboard = QueryOwner->FindComponentByClass<UBlackboardComponent>();
        }
    }
    if(!Blackboard)  return; 

    const auto ActorContext = Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorKeyName));
    UEnvQueryItemType_Actor::SetContextHelper(ContextData, ActorContext);
}
