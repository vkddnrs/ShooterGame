// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ASG_BaseWeapon;
class UEquipFinishedAnimNotify;

USTRUCT()
struct FWeaponData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ASG_BaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly)
    UAnimMontage* ReloadAnimMontage;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

    void StartFire();
    void StopFire();
    void NextWeapon();
    void Reload();

protected:
    UPROPERTY(EditDefaultsOnly, Category = WeaponData)
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    FName WeaponArmourySocketName = "ArmourySocket";

    UPROPERTY(EditDefaultsOnly, Category = Animations)
    UAnimMontage* EquipAnimMontage;

	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    void OnClipEmpty();
    void ChangeClip();

private:
    UPROPERTY()
    ASG_BaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ASG_BaseWeapon*> Weapons;

    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;

    ACharacter* GetCharacter() const;

    int32 CurrentWeaponIndex = 0;
    bool bEquipAnimInProgress = false;
    bool bReloadAnimInProgress = false;

    void SpawnWeapons();
    void PlayAnimMontage(UAnimMontage* Animation);
    void AttachWeaponToSocket(ASG_BaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& WeaponSocketName);
    void EquipWeapon(int32 WeaponIndex); // устанавливает оружие в экипировку (текущее использование)
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* SkeletalMesh);
    void OnReloadFinished(USkeletalMeshComponent* SkeletalMesh);
    bool IsCanFire() const;
    bool IsCanEquip() const;
    bool IsCanReload() const;

    template<typename T>
    T* FindNotifyByClass(const UAnimSequenceBase* Animation) const
    {
        if(!Animation) return nullptr;

        const auto NotifyEvents = Animation->Notifies;
        for(auto NotifyEvent : NotifyEvents)
        {
            auto AnimNotify = Cast<T>(NotifyEvent.Notify);
            if(AnimNotify) return AnimNotify;
        }
        return nullptr;
    }

};
