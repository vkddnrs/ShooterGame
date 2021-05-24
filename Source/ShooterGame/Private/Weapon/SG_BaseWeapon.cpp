// ShooterGame. All Right Reserved.


#include "Weapon/SG_BaseWeapon.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

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
	
}

void ASG_BaseWeapon::MakeShot()
{
    if(!ensure(GetWorld())) return;

    //**
    // We well get ViewLocation and ViewRotation from Character's-Controller's CameraManager
    // through GetPlayerViewPoint.
    const auto Player = Cast<ACharacter>(GetOwner());
    if(!ensure(Player)) return;
    const auto Controller = Player->GetController<APlayerController>();
    if(!ensure(Controller)) return;

    FVector ViewLocation;
    FRotator ViewRotation;
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    //**

    const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
    const FVector TraceStart = ViewLocation;  // SocketTransform.GetLocation();
    const FVector ShootDirection = ViewRotation.Vector();  // SocketTransform.GetRotation().GetForwardVector();
    const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(Player);

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

    if(HitResult.bBlockingHit)
    {
        auto Dot = FVector::DotProduct(SocketTransform.GetRotation().GetForwardVector(), -HitResult.ImpactNormal);

 //       UE_LOG(LogBaseWeapon, Display, TEXT("Dot: %f \nacos(Dot): %f"), Dot, acos(Dot))
 //       if(Dot > 0 && acos(Dot) < 30)

        DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.f, 0, 3.f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 24, FColor::MakeRandomColor(), false, 5.f);

	    UE_LOG(LogBaseWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString())
    }

    else
    {
        DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 3.f, 0, 3.f);
    }

}

void ASG_BaseWeapon::Fire()
{

    UE_LOG(LogBaseWeapon, Display, TEXT("Fire!"))
    MakeShot();
}


