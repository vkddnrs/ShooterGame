// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SGCoreTypes.h"
#include "WeaponComponent.generated.h"

class ASG_BaseWeapon;
class UEquipFinishedAnimNotify;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

    virtual void StartFire();
    void StopFire();
    virtual void NextWeapon();
    void Reload();
    bool TryToAddAmmo(TSubclassOf<ASG_BaseWeapon> WeaponType, int32 ClipsAmount);

    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

protected:
    UPROPERTY(EditDefaultsOnly, Category = WeaponData)
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    FName WeaponArmourySocketName = "ArmourySocket";

    UPROPERTY(EditDefaultsOnly, Category = Animations)
    UAnimMontage* EquipAnimMontage;

    UPROPERTY()
    ASG_BaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ASG_BaseWeapon*> Weapons;

    int32 CurrentWeaponIndex = 0;

	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    void OnClipEmpty(ASG_BaseWeapon* AmmoEmptyWeapon);
    void ChangeClip();
    bool IsCanFire() const;
    bool IsCanEquip() const;
    void EquipWeapon(int32 WeaponIndex);  // Set Weapon in Equip (CurrentWeapon) - устанавливает оружие в экипировку (текущее использование)

private:
    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;

    ACharacter* GetCharacter() const;

    bool bEquipAnimInProgress = false;
    bool bReloadAnimInProgress = false;

    void SpawnWeapons();
    void PlayAnimMontage(UAnimMontage* Animation);
    void AttachWeaponToSocket(ASG_BaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& WeaponSocketName);
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* SkeletalMesh);
    void OnReloadFinished(USkeletalMeshComponent* SkeletalMesh);
    bool IsCanReload() const;

};
