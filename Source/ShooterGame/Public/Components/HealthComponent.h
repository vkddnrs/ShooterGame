// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

    float GetHealth() const { return Health; }

    FOnDeath OnDeath; // will called if Health <= 0
    FOnHealthChanged OnHealthChanged;

protected:
	virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health, meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float MaxHealth = 100.f;

    UFUNCTION(BlueprintCallable)
    bool IsDead() const { return Health <= 0.f; }

private:
    float Health = 0.f;

    UFUNCTION()
    void OnTakeAnyDamageHandle(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
 

};
