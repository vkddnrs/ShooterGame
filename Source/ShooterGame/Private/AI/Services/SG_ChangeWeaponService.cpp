// ShooterGame. All Right Reserved.


#include "AI/Services/SG_ChangeWeaponService.h"
#include "AIController.h"
#include "Components/AI_WeaponComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

USG_ChangeWeaponService::USG_ChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void USG_ChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(Controller && !FMath::IsNearlyZero(Probability))
    {
        const auto Pawn = Controller->GetPawn();
        if(Pawn && FMath::FRandRange(0.f, 1.f) <= Probability)
        {   
            if(const auto WeaponComponent = Pawn->FindComponentByClass<UAI_WeaponComponent>())
            {
                WeaponComponent->NextWeapon();
            }             
        }
    }
         
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
