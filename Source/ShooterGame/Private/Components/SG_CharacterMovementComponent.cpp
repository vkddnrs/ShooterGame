// ShooterGame. All Right Reserved.


#include "SG_CharacterMovementComponent.h"
#include "SG_BaseCharacter.h"

float USG_CharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ASG_BaseCharacter* Player = Cast<ASG_BaseCharacter>(GetOwner());
    return Player && Player->IsRunning() ? MaxSpeed * RunModefier : MaxSpeed;
}
