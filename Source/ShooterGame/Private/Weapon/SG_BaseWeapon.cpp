// ShooterGame. All Right Reserved.


#include "Weapon/SG_BaseWeapon.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
//#include "GameFramework/Controller.h"

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

    CurrentAmmo = DefaultsAmmo;
}

void ASG_BaseWeapon::MakeShot()
{
    //UE_LOG(LogBaseWeapon, Display, TEXT("MakeShot"))
}

void ASG_BaseWeapon::StartFire()
{
    //UE_LOG(LogBaseWeapon, Display, TEXT("Fire!"))
}

void ASG_BaseWeapon::StopFire()
{  
}

APlayerController* ASG_BaseWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if(!ensure(Player)) return nullptr;

    return Player->GetController<APlayerController>();
}

bool ASG_BaseWeapon::GetPlayerViewpoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const APlayerController* Controller = GetPlayerController();
    if(!ensure(Controller)) return false;

    GetPlayerController()->GetPlayerViewPoint(ViewLocation, ViewRotation);
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

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void ASG_BaseWeapon::MakeDamage(const FHitResult& HitResult)
{
    auto DamagedActor = HitResult.GetActor();
    if(DamagedActor && DamagedActor->IsA<ACharacter>())
    {
         DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
    }
}

void ASG_BaseWeapon::DecreaseAmmo()
{
    CurrentAmmo.Bullets--;
    LogAmmo();
    if(IsClipEmpty() && !IsAmmoEmpty())
    {
        ChangeClip();
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

void ASG_BaseWeapon::ChangeClip()
{
    CurrentAmmo.Bullets = DefaultsAmmo.Bullets;
    if(!CurrentAmmo.bInfinite) CurrentAmmo.Clips--;
    UE_LOG(LogBaseWeapon, Display, TEXT("------------ CChangeClip ------------"))
    LogAmmo();
}

void ASG_BaseWeapon::LogAmmo()
{
    FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
    AmmoInfo += CurrentAmmo.bInfinite ? "Infinit" : FString::FromInt(CurrentAmmo.Clips);

    UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo)
}