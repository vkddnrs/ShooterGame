// ShooterGame. All Right Reserved.


#include "Weapon/Components/WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values for this component's properties
UWeaponFXComponent::UWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}




