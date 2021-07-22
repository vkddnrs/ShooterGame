// ShooterGame. All Right Reserved.


#include "Weapon/RifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/WeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"


ARifleWeapon::ARifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<UWeaponFXComponent>("WeaponFXComponent");
}

void ARifleWeapon::BeginPlay()
{
    Super::BeginPlay();

    if(const auto Controller = Cast<APlayerController>(GetController()))
    {
        FOV_CameraDefault = Controller->PlayerCameraManager->GetFOVAngle();
    }
}

void ARifleWeapon::StartFire()
{
    InitFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ARifleWeapon::MakeShot, TimeBetweenShots, true);
    MakeShot();
}

void ARifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetFXVActive(false);
}

void ARifleWeapon::Zoom(bool Enabled)
{
    const auto Controller = Cast<APlayerController>(GetController());
    if(!Controller || !Controller->PlayerCameraManager) return;

    Controller->PlayerCameraManager->SetFOV(Enabled ? FOV_ZoomAngle : FOV_CameraDefault);
}

void ARifleWeapon::MakeShot()
{
    //Super::MakeShot();

    if(!GetWorld()) return;

    if(IsAmmoEmpty())
    {
        StopFire();
        if(!IsAmmoInfinit())
        {
            UGameplayStatics::SpawnSoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
        } 
        return;
    }       

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

void ARifleWeapon::InitFX()
{
    if(!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }

    if(!FireAudioComponent)
    {
        FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
    }
    SetFXVActive(true);
}

void ARifleWeapon::SetFXVActive(bool IsActive)
{
    if(!MuzzleFXComponent) return;

    MuzzleFXComponent->SetPaused(!IsActive);
    MuzzleFXComponent->SetVisibility(IsActive, true);

    if(FireAudioComponent)
    {
        IsActive ? FireAudioComponent->Play() : FireAudioComponent->Stop();
    }
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
    if(!DamagedActor) return;

    FPointDamageEvent PointDamageEvent;
    PointDamageEvent.HitInfo = HitResult;
    DamagedActor->TakeDamage(DamageAmount, PointDamageEvent, GetController(), this);
    
}