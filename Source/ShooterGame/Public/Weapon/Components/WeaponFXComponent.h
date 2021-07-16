// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SG_CoreTypes.h"
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
    //FImpactData GetEffect() const { return DefaultImpactData; } 

protected:
    UPROPERTY(EditDefaultsOnly, Category = VFX)
    FImpactData DefaultImpactData;

    UPROPERTY(EditDefaultsOnly, Category = VFX)
    TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;

};
