// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SG_BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SHOOTERGAME_API ASG_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
    // для подключения в конструкторе нашего кастомного SG_CharacterMovementComponent
	ASG_BaseCharacter(const FObjectInitializer& ObjInit); 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
///////////////////////////////

public:
    UFUNCTION(BlueprintCallable, Category = Movement)
    bool IsRunning() const;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
    UCameraComponent* CameraComponent;

    UPROPERTY(BlueprintReadOnly)
    bool OnRunning = false;

private:
    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void OnStartRunning();
    void OnStopRunning();

    bool WantsToRun = false;
    bool IsMovingForward = false;


   

};
