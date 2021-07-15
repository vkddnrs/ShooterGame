// ShooterGame. All Right Reserved.


#include "Weapon/LauncherWeapon.h"
#include "Weapon/Bombshell.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void ALauncherWeapon::StartFire()
{
    MakeShot();
}

void ALauncherWeapon::MakeShot()
{
    Super::MakeShot();  

    if(!GetWorld()) return;

    if(IsAmmoEmpty())
    {
        UGameplayStatics::SpawnSoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
        return;
    }  

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
    SpawnMuzzleFX();

    UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
}