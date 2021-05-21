// ShooterGame. All Right Reserved.


#include "UI/GameHUD.h"
#include "Engine/Canvas.h"

void AGameHUD::DrawHUD()
{
    Super::DrawHUD();

    DrowCrossHair();
}

void AGameHUD::DrowCrossHair()
{
    const TInterval<float> Center(Canvas->SizeX / 2.f, Canvas->SizeY / 2.f);
    const float HalfLineSize = 10.f;
    const float LineThickness = 2.f;
    const FLinearColor LineColor = FLinearColor::Green;
    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max,
         LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize,
         LineColor, LineThickness);
}
