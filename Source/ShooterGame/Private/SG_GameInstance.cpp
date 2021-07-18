// ShooterGame. All Right Reserved.

#include "SG_GameInstance.h"
#include "Sound/SG_SoundFuncLib.h"

void USG_GameInstance::ToggleVolume()
{
    USG_SoundFuncLib::ToggleSoundClassVolume(MasterSoundClass);
}
