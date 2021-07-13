// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SG_CoreTypes.h"
#include "HealthComponent.generated.h"

//class UCameraShake;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTERGAME_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHealthComponent();

    FOnDeathSignature OnDeath;  // will called if Health <= 0
    FOnHealthChangedSignature OnHealthChanged;

    UFUNCTION(BlueprintCallable, Category = Health)
    bool IsDead() const { return FMath::IsNearlyZero(Health); }

    UFUNCTION(BlueprintCallable, Category = Health)
    float GetHealthPercent() const { return Health / MaxHealth; }

    float GetHealth() const { return Health; }
    bool TryAddHealthAmount(float HealthAmount);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health, meta = (ClampMin = "1.0", ClampMax = "1000.0"))
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

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = VFX)
    TSubclassOf<UCameraShakeBase> CameraShake;

private:
    float Health = 0.f;
    FTimerHandle HealTimerHandle;

    void HealUpdate();
    void SetHealth(float NewHealth);
    bool IsHealthFull() const;
    void PlayCameraShake();

    UFUNCTION()
    void OnTakeAnyDamageHandle(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    // Calls method ASG_GameModeBase::Killed(), passing the killer and victim (self) controllers to it.
    void Killed(AController* KillerController) const;

};