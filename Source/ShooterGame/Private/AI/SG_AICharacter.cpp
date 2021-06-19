// ShooterGame. All Right Reserved.


#include "AI/SG_AICharacter.h"
#include "AI/SG_AIController.h"
#include "SG_CharacterMovementComponent.h"
#include "AI_WeaponComponent.h"


ASG_AICharacter::ASG_AICharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UAI_WeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASG_AIController::StaticClass();

    // **************** ��������� ��� �������� �������� AI ��������� **************

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
