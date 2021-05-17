// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SG_BaseCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UHealthComponent;
class UTextRenderComponent;

UCLASS()
class SHOOTERGAME_API ASG_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
    // для подключения в конструкторе нашего кастомного SG_CharacterMovementComponent
	ASG_BaseCharacter(const FObjectInitializer& ObjInit); 

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
    UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
    UHealthComponent* HealthComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
    UTextRenderComponent* TextRenderComponent;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = Movement)
    bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category = Movement)
    float GetMovementDirection() const;

private:
    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void OnStartRunning();
    void OnStopRunning();

    bool WantsToRun = false;
    bool IsMovingForward = false;

   

};
