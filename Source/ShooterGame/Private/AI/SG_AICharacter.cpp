// ShooterGame. All Right Reserved.


#include "AI/SG_AICharacter.h"
#include "AI/SG_AIController.h"
#include "SG_CharacterMovementComponent.h"
#include "AI_WeaponComponent.h"
#include "BrainComponent.h"


ASG_AICharacter::ASG_AICharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UAI_WeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ASG_AIController::StaticClass();

    // **************** установки для плавного вращения AI персонажа **************

    bUseControllerRotationYaw = false;
    if(GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.f, 200.f, 0.f);
    }
    //********************
}

void ASG_AICharacter::BeginPlay()
{
    Super :: BeginPlay();

}

void ASG_AICharacter::OnDeath()
{
    Super::OnDeath();

    const auto AIController = Cast<AAIController>(Controller);
    if(AIController && AIController->BrainComponent)
    {
        AIController->BrainComponent->Cleanup(); // stop BehaviorTree
    }
}
