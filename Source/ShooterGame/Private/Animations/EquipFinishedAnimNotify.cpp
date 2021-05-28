// ShooterGame. All Right Reserved.


#include "Animations/EquipFinishedAnimNotify.h"

void UEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super :: Notify(MeshComp, Animation);
}
