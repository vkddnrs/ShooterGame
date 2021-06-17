// ShooterGame. All Right Reserved.


#include "AI/SG_AICharacter.h"
#include "AI/SG_AIController.h"
#include "SG_CharacterMovementComponent.h"


ASG_AICharacter::ASG_AICharacter(const FObjectInitializer& ObjInit)
     : Super(ObjInit)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
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
//    ensure(BehaviorTreeAsset);
}
