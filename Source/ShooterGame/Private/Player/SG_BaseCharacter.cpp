// ShooterGame. All Right Reserved.


#include "SG_BaseCharacter.h"

#include <string>

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SG_CharacterMovementComponent.h"
#include "HealthComponent.h"
#include "Components/TextRenderComponent.h"

DEFINE_LOG_CATEGORY_STATIC(Log_SG_BaseCharacter, All, All)

// Sets default values
// подключение в конструкторе нашего кастомного SG_CharacterMovementComponent
ASG_BaseCharacter::ASG_BaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USG_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
   
    HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

    TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
    TextRenderComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ASG_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    check(HealthComponent);
    check(TextRenderComponent);
    check(GetCharacterMovement());

    OnHealthChangedHandle(HealthComponent->GetHealth());

    HealthComponent->OnDeath.AddUObject(this, &ASG_BaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASG_BaseCharacter::OnHealthChangedHandle);
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
    PlayerInputComponent->BindAxis("LookUp", this, &ASG_BaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASG_BaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ASG_BaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ASG_BaseCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ASG_BaseCharacter::OnStopRunning);
}

void ASG_BaseCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0.f;

    if (Amount == 0.f) return;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASG_BaseCharacter::MoveRight(float Amount)
{
    if (Amount == 0.f) return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void ASG_BaseCharacter::OnStartRunning()
{
    WantsToRun = true;

    //if (FVector::DotProduct(GetVelocity(), GetActorForwardVector()) == 1)
    //{
    //    OnRunning = true;
    //    GetCharacterMovement()->MaxWalkSpeed *= 2;
    //}
}

void ASG_BaseCharacter::OnStopRunning()
{
    WantsToRun = false;

    //if (OnRunning)
    //{
    //    OnRunning = false;
    //    GetCharacterMovement()->MaxWalkSpeed /= 2;
    //}

}

void ASG_BaseCharacter::OnDeath()
{
    UE_LOG(Log_SG_BaseCharacter, Display, TEXT("Player %s is death"), *GetName())
}

void ASG_BaseCharacter::OnHealthChangedHandle(float Health)
{
    if(ensure(TextRenderComponent))
    {
        TextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
    }
}


bool ASG_BaseCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float ASG_BaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) return 0.f;

    const FVector VelocityNorm = GetVelocity().GetSafeNormal();
    const float AngleBetween = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNorm)));
    const FVector CrossProduct = FVector::CrossProduct(GetActorForwardVector(), GetVelocity());

    return CrossProduct.IsZero() ? AngleBetween : AngleBetween * FMath::Sign(CrossProduct.Z);
}


