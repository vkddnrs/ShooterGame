// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SG_BaseCharacter.generated.h"

class UHealthComponent;
class UWeaponComponent;
class USoundCue;

UCLASS()
class SHOOTERGAME_API ASG_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
    // для подключения в конструкторе нашего кастомного SG_CharacterMovementComponent
	ASG_BaseCharacter(const FObjectInitializer& ObjInit);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
    UHealthComponent* HealthComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
    UWeaponComponent* WeaponComponent;

    UPROPERTY(EditDefaultsOnly, Category = Animation)
    UAnimMontage* DeathAnimMontage;

    // The time after which the killed character is removed from the field.
    UPROPERTY(EditDefaultsOnly, Category = Damage)
    float LifeSpanOnDeath = 5.f; 

    // The range of the speed of falling to the ground, within which
    // we apply differential damage to the character.
    UPROPERTY(EditDefaultsOnly, Category = Damage)
    FVector2D LandedDamageVelocity = FVector2D(700.f, 1200.0f);

    // The range of damage applied to the character when falling to the ground.
    UPROPERTY(EditDefaultsOnly, Category = Damage)
    FVector2D LandedDamage = FVector2D(10.f, 100.0f);

    UPROPERTY(EditDefaultsOnly, Category = Material)
    FName MaterialColorName = "Paint Color";

    UPROPERTY(EditDefaultsOnly, Category = Sound)
    USoundCue* DeathSound;

    virtual void BeginPlay() override;
    virtual void OnDeath();
    virtual void OnHealthChanged(float Health, float DeltaHealth);

public:	
	virtual void Tick(float DeltaTime) override;
    void SetPlayerColor(const FLinearColor& Color);

    UFUNCTION(BlueprintCallable, Category = Movement)
    virtual bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category = Movement)
    float GetMovementDirection() const;

private:
    UFUNCTION()
    void OnGroundLanded(const FHitResult& HitResult);


};
