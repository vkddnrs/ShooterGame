// ShooterGame. All Right Reserved.


#include "SG_BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ASG_BaseCharacter::ASG_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
    CameraComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ASG_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASG_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASG_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ASG_BaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASG_BaseCharacter::MoveRight);

}

void ASG_BaseCharacter::MoveForward(float Amount)
{
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASG_BaseCharacter::MoveRight(float Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}

