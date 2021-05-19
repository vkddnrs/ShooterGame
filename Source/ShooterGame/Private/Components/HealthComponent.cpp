// ShooterGame. All Right Reserved.


#include "Components/HealthComponent.h"
#include "FireDamageType.h"
#include "IceDamageType.h"

DECLARE_LOG_CATEGORY_CLASS(LogHealthComponent, All, All)

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;


}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
    OnHealthChanged.Broadcast(Health);
    
    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamageHandle);
    }
}


void UHealthComponent::OnTakeAnyDamageHandle(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if(Damage <= 0.f || IsDead()) { return; }

    Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
    OnHealthChanged.Broadcast(Health);

    if(IsDead())
    {
        OnDeath.Broadcast();
    }
}