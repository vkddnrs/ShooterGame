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

    void StartFire();
    void StopFire();
    void NextWeapon();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TArray<TSubclassOf<ASG_BaseWeapon>> WeaponClasses;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    FName WeaponArmourySocketName = "ArmourySocket";

    UPROPERTY(EditDefaultsOnly, Category = Animations)
    UAnimMontage* EquipAnimMontage;

	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    UPROPERTY()
    ASG_BaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ASG_BaseWeapon*> Weapons;

    ACharacter* GetCharacter();
    void SpawnWeapons();
    void PlayAnimMontage(UAnimMontage* Animation);
    void AttachWeaponToSocket(ASG_BaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& WeaponSocketName);
    void EquipWeapon(int32 WeaponIndex); // устанавливает оружие в экипировку (текущее использование)
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* SkeletalMesh);
    bool IsCanFire() const;
    bool IsCanEquip() const;

    int32 CurrentWeaponIndex = 0;
    bool bEquipAnimInProgress = false;

};
