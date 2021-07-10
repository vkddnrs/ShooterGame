// ShooterGame. All Right Reserved.

#include "AI/SG_AICharacter.h"
#include "AI/SG_AIController.h"
#include "SG_CharacterMovementComponent.h"
#include "AI_WeaponComponent.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/SG_HealthBarWidget.h"
#include "Components/HealthComponent.h"

ASG_AICharacter::ASG_AICharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UAI_WeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ASG_AIController::StaticClass();

    // **************** установки для плавного вращения AI персонажа **************

    bUseControllerRotationYaw = false;
    if(GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.f, 200.f, 0.f);
    }
    //********************

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void ASG_AICharacter::BeginPlay()
{
    Super ::BeginPlay();

    check(HealthWidgetComponent);

    if(GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(
            HealthWidgetVisibilityTimerHandle, this, &ASG_AICharacter::UpdateHealthWidgetVisibility, 1.f, true);
    }
}

void ASG_AICharacter::OnDeath()
{
    Super::OnDeath();

    const auto AIController = Cast<AAIController>(Controller);
    if(AIController && AIController->BrainComponent)
    {
        AIController->BrainComponent->Cleanup();  // stop BehaviorTree
    }
}

void ASG_AICharacter::OnHealthChanged(float Health, float DeltaHealth)
{
    Super::OnHealthChanged(Health, DeltaHealth);

    // get UserWidget that we installed in the blueprint
    const auto HealthBarWidget = Cast<USG_HealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if(!HealthBarWidget) return;

    HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void ASG_AICharacter::UpdateHealthWidgetVisibility()
{
    if(!GetWorld() ||                                          //
        !GetWorld()->GetFirstPlayerController() ||             //
        !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator())  
        return;

    const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
    const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
    HealthWidgetComponent->SetVisibility(Distance <= HealthWidgetVisibilityDistance, true);
}
