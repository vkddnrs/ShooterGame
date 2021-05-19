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

    // Turn on / off automatic health regeneration.
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Heal)
    bool AutoHeal = true;

    // The time intervals between increases in health points.
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Heal, meta = (EditCondition = "AutoHeal"))
    float HealUpdateTime = 0.5f;

    // Delay before starting health regeneration.
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Heal, meta = (EditCondition = "AutoHeal"))
    float HealDelay = 3.f;

    // The value of a single change in health points.
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Heal, meta = (EditCondition = "AutoHeal"))
    float HealModifier = 5.f;

    UFUNCTION(BlueprintCallable)
    bool IsDead() const { return FMath::IsNearlyZero(Health); }

private:
    float Health = 0.f;
    FTimerHandle HealTimerHandle;

    void HealUpdate();
    void SetHealth(float NewHealth);

    UFUNCTION()
    void OnTakeAnyDamageHandle(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
 

};
