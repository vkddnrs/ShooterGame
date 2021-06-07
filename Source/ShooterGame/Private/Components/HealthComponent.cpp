// ShooterGame. All Right Reserved.


#include "Components/HealthComponent.h"
#include "TimerManager.h" 

DECLARE_LOG_CATEGORY_CLASS(LogHealthComponent, All, All)

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

    SetHealth(MaxHealth);
    check(MaxHealth > 0)
    
    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamageHandle);
}


void UHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);

    if(FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld()) 
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

}

// Set Health and invoke Broadcast
void UHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp<float>(NewHealth, 0.f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}

bool UHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

void UHealthComponent::OnTakeAnyDamageHandle(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if(!ensure(GetWorld())) return;

    //UE_LOG(LogHealthComponent, Warning, TEXT("I: %s tike damage from %s"), *GetOwner()->GetName(), *DamageCauser->GetName())

    if(Damage <= 0.f || IsDead())  return; 

    // if Heal is active - we stopping him
    if(GetWorld()->GetTimerManager().IsTimerActive(HealTimerHandle))
         GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

    SetHealth(Health - Damage);
    if(IsDead())
        OnDeath.Broadcast();
    else if(Health < MaxHealth && AutoHeal && GetWorld())
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
}

bool UHealthComponent::TryAddHealthAmount(float HealthAmount)
{
    if(IsHealthFull()) return false;

    SetHealth(Health + HealthAmount);
    return true;
}