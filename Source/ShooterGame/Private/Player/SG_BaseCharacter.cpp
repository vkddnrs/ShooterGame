// ShooterGame. All Right Reserved.


#include "SG_BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SG_CharacterMovementComponent.h"
#include "HealthComponent.h"
#include "Weapon/SG_BaseWeapon.h"
#include "Components/WeaponComponent.h"
#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY_STATIC(Log_SG_BaseCharacter, All, All)

// Sets default values
// подключение в конструкторе нашего кастомного SG_CharacterMovementComponent
ASG_BaseCharacter::ASG_BaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USG_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
    WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void ASG_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    check(HealthComponent);
    check(GetCharacterMovement());
    check(GetMesh());

    OnHealthChanged(HealthComponent->GetHealth(), 0.f);

    HealthComponent->OnDeath.AddUObject(this, &ASG_BaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASG_BaseCharacter::OnHealthChanged);
    LandedDelegate.AddDynamic(this, &ASG_BaseCharacter::OnGroundLanded);

    GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

}

// Called every frame
void ASG_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ASG_BaseCharacter::SetPlayerColor(const FLinearColor& Color)
{
    const auto MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if(!MaterialInstance) return;
    MaterialInstance->SetVectorParameterValue(MaterialColorName, Color);
}


void ASG_BaseCharacter::OnDeath()
{
    // UE_LOG(Log_SG_BaseCharacter, Display, TEXT("Player %s is death"), *GetName())
    //PlayAnimMontage(DeathAnimMontage);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(LifeSpanOnDeath);

    // Disabling collisions in the capsule component.
    // Отключаем коллизии в компоненте капсулы
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}

void ASG_BaseCharacter::OnHealthChanged(float Health, float DeltaHealth)
{
 
}


bool ASG_BaseCharacter::IsRunning() const
{
    return false;
}

float ASG_BaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) return 0.f;

    const FVector VelocityNorm = GetVelocity().GetSafeNormal();
    const float AngleBetween = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNorm)));
    const FVector CrossProduct = FVector::CrossProduct(GetActorForwardVector(), GetVelocity());

    return CrossProduct.IsZero() ? AngleBetween : AngleBetween * FMath::Sign(CrossProduct.Z);
}


void ASG_BaseCharacter::OnGroundLanded(const FHitResult& HitResult)
{
    const auto FallVelocityZ = abs(GetVelocity().Z);
    //UE_LOG(Log_SG_BaseCharacter, Display, TEXT("On landed FallVelocityZ: %f"), FallVelocityZ)

    if(FallVelocityZ < LandedDamageVelocity.X) return;

    const auto Damage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    TakeDamage(Damage, FDamageEvent(), nullptr, nullptr);

    UE_LOG(Log_SG_BaseCharacter, Display, TEXT("Damage: %f"), Damage)

}


