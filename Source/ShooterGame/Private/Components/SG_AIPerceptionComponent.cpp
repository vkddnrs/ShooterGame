// ShooterGame. All Right Reserved.


#include "Components/SG_AIPerceptionComponent.h"
#include "AIController.h"
#include "Components/HealthComponent.h"
#include "Perception/AISense_Sight.h"
//#include "ProjectUtils.h"


AActor* USG_AIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
    if(PercieveActors.Num() == 0) return nullptr;

    const auto Controller = Cast<AAIController>(GetOwner());
    if(!Controller) return nullptr;

    const auto Pawn = Controller->GetPawn();
    if(!Pawn) return nullptr;

    float ClosestDistance = MAX_FLT;
    AActor* ClosestPawn = nullptr;
    
    for (const auto CurrActor : PercieveActors)
    {
        const auto HealthComponent = CurrActor->FindComponentByClass<UHealthComponent>();
        if(!HealthComponent || HealthComponent->IsDead()) continue; // TODO check if enemies or not

        const auto CurrentDistance = (CurrActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
        if(CurrentDistance < ClosestDistance)
        {
            ClosestDistance = CurrentDistance;
            ClosestPawn = CurrActor;
        }
    }
    return ClosestPawn;
}
