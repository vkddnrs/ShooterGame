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

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamageHandle);
    }
}


void UHealthComponent::OnTakeAnyDamageHandle(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    Health -= Damage;
    UE_LOG(LogHealthComponent, Display, TEXT("Damage : %f"), Damage)

    if (DamageType)
    {
        if (DamageType->IsA<UFireDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("So hooooooooot!!!!!!"))
        }
        else if (DamageType->IsA<UIceDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("So coooold!!!!!!!"))
        }
    }

}