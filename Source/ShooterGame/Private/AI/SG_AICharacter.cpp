// ShooterGame. All Right Reserved.


#include "AI/SG_AICharacter.h"
#include "AI/SG_AIController.h"

ASG_AICharacter::ASG_AICharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASG_AIController::StaticClass();

}
