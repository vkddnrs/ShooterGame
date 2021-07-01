// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/SG_BaseCharacter.h"
#include "SG_PlayerCharacter.generated.h"

class USpringArmComponent;	
class UCameraComponent;

UCLASS()
class SHOOTERGAME_API ASG_PlayerCharacter : public ASG_BaseCharacter
{
	GENERATED_BODY()
public:
    ASG_PlayerCharacter(const FObjectInitializer& ObjInit);


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
    UCameraComponent* CameraComponent;

    virtual void OnDeath() override;

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual bool IsRunning() const override;

private:
    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void OnStartRunning();
    void OnStopRunning();

    bool WantsToRun = false;
    bool IsMovingForward = false;
};
