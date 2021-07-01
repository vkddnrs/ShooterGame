// ShooterGame. All Right Reserved.


#include "Player/SG_PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/WeaponComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

ASG_PlayerCharacter::ASG_PlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.f, 100.f, 80.f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
    CameraCollisionComponent->SetupAttachment(CameraComponent);
    CameraCollisionComponent->SetSphereRadius(10.f);
    CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

// Called to bind functionality to input
void ASG_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if(!ensure(PlayerInputComponent)) return;
    if(!ensure(WeaponComponent)) return;

    PlayerInputComponent->BindAxis("MoveForward", this, &ASG_PlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASG_PlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ASG_PlayerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASG_PlayerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ASG_PlayerCharacter::Jump);
    PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ASG_PlayerCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ASG_PlayerCharacter::OnStopRunning);
    PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, WeaponComponent, &UWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, WeaponComponent, &UWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", EInputEvent::IE_Pressed, WeaponComponent, &UWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, WeaponComponent, &UWeaponComponent::Reload);
}

void ASG_PlayerCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0.f;

    if (Amount == 0.f) return;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASG_PlayerCharacter::MoveRight(float Amount)
{
    if (Amount == 0.f) return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void ASG_PlayerCharacter::OnStartRunning()
{
    WantsToRun = true;
}

void ASG_PlayerCharacter::OnStopRunning()
{
    WantsToRun = false;
}

void ASG_PlayerCharacter::CheckCameraOverlap()
{
    const bool HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
    GetMesh()->SetOwnerNoSee(HideMesh);

    TArray<USceneComponent*> MeshChildren;
    GetMesh()->GetChildrenComponents(true, MeshChildren);

    for(auto MeshChild : MeshChildren)
    {
        const auto MeshGeometry = Cast<UPrimitiveComponent>(MeshChild);
        if(MeshGeometry)
        {
            MeshGeometry->SetOwnerNoSee(HideMesh);
        }
    }
}

void ASG_PlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    CheckCameraOverlap();
}

void ASG_PlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    CheckCameraOverlap();
}

bool ASG_PlayerCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

void ASG_PlayerCharacter::OnDeath()
{
    Super::OnDeath();

    if(Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void ASG_PlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    ensure(CameraCollisionComponent);

    CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASG_PlayerCharacter::OnCameraCollisionBeginOverlap);
    CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASG_PlayerCharacter::OnCameraCollisionEndOverlap);

}
