// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API UWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponFXComponent();

    void PlayImpactFX(const FHitResult& Hit);
    UNiagaraSystem* GetEffect() const { return DefaultEffect; } 

protected:
    UPROPERTY(EditDefaultsOnly, Category = VFX)
    UNiagaraSystem* DefaultEffect;

    UPROPERTY(EditDefaultsOnly, Category = VFX)
    TMap<UPhysicalMaterial*, UNiagaraSystem*> EffectsMap;
};
