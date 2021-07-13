// ShooterGame. All Right Reserved.


#include "UI/SG_BaseWidget.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

void USG_BaseWidget::Show()
{
    PlayAnimation(ShowAnimation);
    if(GetWorld() && OpenSound)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), OpenSound);
    }
}
