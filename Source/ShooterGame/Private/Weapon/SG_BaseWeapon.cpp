// ShooterGame. All Right Reserved.

#include "Weapon/SG_BaseWeapon.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
// #include "Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Engine/SkeletalMeshSocket.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

// Sets default values
ASG_BaseWeapon::ASG_BaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

// Called when the game starts or when spawned
void ASG_BaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    ensure(WeaponMesh);
    // checkf(DefaultsAmmo.Bullets > 0, TEXT("Bullets count couldn't be less or equal zero"))
    // checkf(DefaultsAmmo.Clips > 0, TEXT("Clips count couldn't be less or equal zero"))

    if(!ensure(DefaultsAmmo.Bullets > 0)) UE_LOG(LogBaseWeapon, Error, TEXT("Bullets count couldn't be less or equal zero"))
    if(!ensure(DefaultsAmmo.Clips > 0)) UE_LOG(LogBaseWeapon, Error, TEXT("Clips count couldn't be less or equal zero"))

    CurrentAmmo = DefaultsAmmo;
}

void ASG_BaseWeapon::MakeShot()
{
    // UE_LOG(LogBaseWeapon, Display, TEXT("MakeShot"))
}

void ASG_BaseWeapon::StartFire()
{
    // UE_LOG(LogBaseWeapon, Display, TEXT("Fire!"))
}

void ASG_BaseWeapon::StopFire() {}

bool ASG_BaseWeapon::GetPlayerViewpoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto Player = Cast<ACharacter>( GetOwner());
    if(!Player) return false;

    if(Player->IsPlayerControlled())
    {
        const APlayerController* Controller = Player->GetController<APlayerController>();
        if(!ensure(Controller)) return false;

        Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);       
    }
    else
    {
        ViewLocation = GetMuzzleWorldLocation();
        ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
    }
    return true;
}

FVector ASG_BaseWeapon::GetMuzzleWorldLocation() const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASG_BaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    // We well get ViewLocation and ViewRotation from Character's-Controller's CameraManager
    // through GetPlayerViewPoint.
    FVector ViewLocation;
    FRotator ViewRotation;
    if(!GetPlayerViewpoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    return true;
}

void ASG_BaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const
{
    if(!ensure(GetWorld())) return;

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());
    CollisionParams.bReturnPhysicalMaterial = true;  // for definition of FVX

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}


void ASG_BaseWeapon::DecreaseAmmo()
{
    if(CurrentAmmo.Bullets == 0)
    {
        //UE_LOG(LogBaseWeapon, Display, TEXT("Clip is empty"))
        return;
    }

    CurrentAmmo.Bullets--;
    // LogAmmo();
    if(IsClipEmpty() && !IsAmmoEmpty())
    {
        StopFire();
        OnClipEmpty.Broadcast(this);
    }
}

bool ASG_BaseWeapon::IsAmmoEmpty() const
{
    return !CurrentAmmo.bInfinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ASG_BaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}

bool ASG_BaseWeapon::IsAmmoFull() const
{
    return CurrentAmmo.Clips == DefaultsAmmo.Clips &&  //
           CurrentAmmo.Bullets == DefaultsAmmo.Bullets;
}

void ASG_BaseWeapon::ChangeClip()
{
    if(!CurrentAmmo.bInfinite)
    {
        if(CurrentAmmo.Clips == 0)
        {
            //UE_LOG(LogBaseWeapon, Display, TEXT("No more clip"))
            return;
        }
        CurrentAmmo.Clips--;
        //UE_LOG(LogBaseWeapon, Display, TEXT("------------ ChangeClip ------------"))
    }

    CurrentAmmo.Bullets = DefaultsAmmo.Bullets;
    // LogAmmo();
}

bool ASG_BaseWeapon::IsCanReload() const
{
    return CurrentAmmo.Bullets < DefaultsAmmo.Bullets && CurrentAmmo.Clips > 0;
}

bool ASG_BaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
    if(CurrentAmmo.bInfinite || IsAmmoFull() || ClipsAmount <= 0) return false;

    bool bReload = false;
    int32 MaxClips = DefaultsAmmo.Clips;
    if(CurrentAmmo.Bullets < DefaultsAmmo.Bullets && CurrentAmmo.Clips + ClipsAmount > DefaultsAmmo.Clips)
    {
        bReload = true;
        MaxClips += 1;
    }

    CurrentAmmo.Clips = FMath::Clamp<int>(CurrentAmmo.Clips + ClipsAmount, 1, MaxClips);

    if(bReload || CurrentAmmo.Bullets == 0)
    {
        OnClipEmpty.Broadcast(this);
    }

    //UE_LOG(LogBaseWeapon, Warning, TEXT("TryToAddAmmo CurrentAmmo.Clips : %i"), CurrentAmmo.Clips)
    return true;
}

void ASG_BaseWeapon::LogAmmo()
{
    FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
    AmmoInfo += CurrentAmmo.bInfinite ? "Infinit" : FString::FromInt(CurrentAmmo.Clips);

    //UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo)
}

UNiagaraComponent* ASG_BaseWeapon::SpawnMuzzleFX()
{
    return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX,  //
        WeaponMesh,                                                //
        MuzzleSocketName,                                          //
        FVector::ZeroVector,                                       //
        FRotator::ZeroRotator,                                     //
        EAttachLocation::SnapToTarget,                             //
        true);
}
