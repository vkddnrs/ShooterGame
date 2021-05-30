// ShooterGame. All Right Reserved.


#include "Weapon/LauncherWeapon.h"
#include "Weapon/Bombshell.h"

void ALauncherWeapon::StartFire()
{
    MakeShot();
}



void ALauncherWeapon::MakeShot()
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

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector StartPoint = GetMuzzleWorldLocation();
    const FVector Direction = (EndPoint - StartPoint).GetSafeNormal();

    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    auto Projectile = GetWorld()->SpawnActorDeferred<ABombshell>(ProjectileClass, SpawnTransform);
    if(ensure(Projectile))
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetLifeSpan(5.f);
        Projectile->FinishSpawning(SpawnTransform);
        Projectile->SetOwner(GetOwner());
    }

    DecreaseAmmo();
}