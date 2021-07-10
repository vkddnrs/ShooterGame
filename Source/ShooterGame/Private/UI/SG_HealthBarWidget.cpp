// ShooterGame. All Right Reserved.


#include "UI/SG_HealthBarWidget.h"
#include "Components/ProgressBar.h"

void USG_HealthBarWidget::SetHealthPercent(float Percent)
{
    if(!HealthProgressBar) return;

    const auto HealthBarVisibility =
        (Percent > 0.f && Percent <= PercentVisibilityThreshold) ? ESlateVisibility::Visible : ESlateVisibility::Hidden;

    HealthProgressBar->SetVisibility(HealthBarVisibility);

    const auto HealthBarColor = Percent <= PercentBadColorThreshold ? BadColor : GoodColor;
    HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

    HealthProgressBar->SetPercent(Percent);
}
