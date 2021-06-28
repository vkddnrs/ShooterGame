// ShooterGame. All Right Reserved.


#include "Weapon/RifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/WeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Character.h"

ARifleWeapon::ARifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<UWeaponFXComponent>("WeaponFXComponent");
}

void ARifleWeapon::BeginPlay()
{
    Super::BeginPlay();

    //ensure(WeaponFXComponent->GetEffect());
}

void ARifleWeapon::StartFire()
{
    InitMuzzleFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ARifleWeapon::MakeShot, TimeBetweenShots, true);
    MakeShot();
}

void ARifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetMuzzleFXVisible(false);
}

void ARifleWeapon::MakeShot()
{
    //Super::MakeShot();

    if(IsAmmoEmpty())
    {
        StopFire();
        return;
    }    

    if(!ensure(GetWorld())) return;

    FVector TraceStart, TraceEnd;
    if(!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    FVector TraceFXEnd = TraceEnd;
    if(HitResult.bBlockingHit)
    {
        TraceFXEnd = HitResult.ImpactPoint;

        MakeDamage(HitResult);
        WeaponFXComponent->PlayImpactFX(HitResult);        
    }
    SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
    //UE_LOG(LogTemp, Display, TEXT("MakeShot"))
    DecreaseAmmo();
}

bool ARifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if(!GetPlayerViewpoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const auto HalfAngleRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfAngleRad);
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    return true;
}

void ARifleWeapon::InitMuzzleFX()
{
    if(!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }
    SetMuzzleFXVisible(true);
}

void ARifleWeapon::SetMuzzleFXVisible(bool Visible)
{
    if(!MuzzleFXComponent) return;

    MuzzleFXComponent->SetPaused(!Visible);
    MuzzleFXComponent->SetVisibility(Visible, true);

}

void ARifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, TraceFX, TraceStart);
    if(TraceFXComponent)
    {
        TraceFXComponent->SetVariableVec3(TraceTargetName, TraceEnd);
    }
}

AController* ARifleWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}

void ARifleWeapon::MakeDamage(const FHitResult& HitResult)
{
    auto DamagedActor = HitResult.GetActor();
    if(DamagedActor && DamagedActor->IsA<ACharacter>())
    {
        DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetController(), this);
    }
}