// ShooterGame. All Right Reserved.


#include "UI/GameHUD.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"
#include "SG_GameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSG_GameHUD, All, All);

void AGameHUD::DrawHUD()
{
    Super::DrawHUD();

    //DrowCrossHair();
}

void AGameHUD::BeginPlay()
{
    Super::BeginPlay();

    if(ensure(PlayerHUDWidgetClass))
    {
        const auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
        if(PlayerHUDWidget)
        {
            PlayerHUDWidget->AddToViewport();
        }
    }

    if(GetWorld())
    {
        const auto GameMode = Cast<ASG_GameModeBase>(GetWorld()->GetAuthGameMode());
        if(GameMode)
        {
            GameMode->OnMathStateChanged.AddUObject(this, &AGameHUD::OnMathStateChanged);
        }
    }

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

void AGameHUD::OnMathStateChanged(ESG_MathState State)
{
    UE_LOG(LogSG_GameHUD, Display, TEXT("MathStateChanged: %s"), *UEnum::GetValueAsString(State))
}
