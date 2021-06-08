// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponFXComponent.generated.h"

class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API UWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponFXComponent();

    void PlayImpactFX(const FHitResult& Hit);
    UNiagaraSystem* GetEffect() const { return Effect; } 

protected:
    UPROPERTY(EditDefaultsOnly, Category = VFX)
    UNiagaraSystem* Effect;


		
};
