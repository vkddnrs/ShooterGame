// ShooterGame. All Right Reserved.


#include "SG_CharacterMovementComponent.h"
#include "SG_BaseCharacter.h"

float USG_CharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ASG_BaseCharacter* Player = Cast<ASG_BaseCharacter>(GetOwner());
    return Player && Player->IsRunning() ? MaxSpeed * RunModefier : MaxSpeed;
}

void USG_CharacterMovementComponent::StartFalling(int32 Iterations, float remainingTime, float timeTick, const FVector& Delta,
    const FVector& subLoc)
{
    Super::StartFalling(Iterations, remainingTime, timeTick, Delta, subLoc);

    if(!GetWorld() || GetWorld()->GetTimerManager().IsTimerActive(TimerFalling)) return;
    GetWorld()->GetTimerManager().SetTimer(TimerFalling, this, &USG_CharacterMovementComponent::OnTimeDeath, TimeFallingOnDeath, false);
}

void USG_CharacterMovementComponent::OnTimeDeath()
{
    if(!GetWorld() || !GetOwner()) return;

    if(IsFalling())
    {
        GetOwner<ASG_BaseCharacter>()->OutGame();
    }
}
