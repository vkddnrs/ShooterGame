// ShooterGame. All Right Reserved.


#include "Sound/SG_SoundFuncLib.h"
#include "Sound/SoundClass.h"

DEFINE_LOG_CATEGORY_STATIC(LogSG_SoundFuncLib, All, All)

void USG_SoundFuncLib::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
    if(!SoundClass) return;

    SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.f, 1.f);
    UE_LOG(LogSG_SoundFuncLib, Display, TEXT("Sound class volume was changed: %s = %f"), *SoundClass->GetName(), 
         SoundClass->Properties.Volume)
}

void USG_SoundFuncLib::ToggleSoundClassVolume(USoundClass* SoundClass)
{
    if(!SoundClass) return;

    const auto NextVolume = SoundClass->Properties.Volume > 0.f ? 0.f : 1.f;
    SetSoundClassVolume(SoundClass, NextVolume);
}
