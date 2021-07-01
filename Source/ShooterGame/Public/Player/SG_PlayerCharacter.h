// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/SG_BaseCharacter.h"
#include "SG_PlayerCharacter.generated.h"

class USpringArmComponent;	
class UCameraComponent;
class USphereComponent;


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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
    USphereComponent* CameraCollisionComponent;

    virtual void OnDeath() override;

public:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual bool IsRunning() const override;

private:
    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void OnStartRunning();
    void OnStopRunning();   
    void CheckCameraOverlap(); // When the camera falls into the mesh, we make the mesh and its children invisible to avoid camera artifact.

    UFUNCTION()
    void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
    void OnCameraCollisionEndOverlap(
        UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    bool WantsToRun = false;
    bool IsMovingForward = false;


};
