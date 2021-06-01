// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "BaseAnimNotify.generated.h"

/**
 *
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*);

UCLASS()
class SHOOTERGAME_API UBaseAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
    FOnNotifiedSignature OnNotified;
};
