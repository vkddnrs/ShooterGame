// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ASG_BaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

    void Fire();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<ASG_BaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    FName WeaponAttachPointName = "WeaponSocket";

	virtual void BeginPlay() override;

private:
    void SpawnWeapon();

    UPROPERTY()
    ASG_BaseWeapon* CurrentWeapon = nullptr;		
};
