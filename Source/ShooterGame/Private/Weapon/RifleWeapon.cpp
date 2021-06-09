// ShooterGame. All Right Reserved.


#include "Weapon/RifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/WeaponFXComponent.h"

ARifleWeapon::ARifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<UWeaponFXComponent>("WeaponFXComponent");
}

void ARifleWeapon::BeginPlay()
{
    Super::BeginPlay();

    ensure(WeaponFXComponent->GetEffect());
}

void ARifleWeapon::StartFire()
{
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ARifleWeapon::MakeShot, TimeBetweenShots, true);
    MakeShot();
}

void ARifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
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

    if(HitResult.bBlockingHit)
    {
        //DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.f, 0, 3.f);
        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 24, FColor::MakeRandomColor(), false, 5.f);

        MakeDamage(HitResult);
        WeaponFXComponent->PlayImpactFX(HitResult);
        // UE_LOG(LogBaseWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString())
    }

    else
    {
        //DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.f, 0, 3.f);
    }

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
