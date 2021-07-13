// ShooterGame. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SG_CoreTypes.h"
#include "SG_LevelItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

UCLASS()
class SHOOTERGAME_API USG_LevelItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    FOnLevelSelectedSignature OnLevelSelected;

    void SetLevelData(const FLevelData& Data);
    FLevelData GetLevelData() { return LevelData; }

    void SetSelected(bool IsSelected);

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* LevelSelectButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* LevelNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage* LevelImage = nullptr;

    UPROPERTY(meta = (BindWidget))
    UImage* FrameImage = nullptr;

    virtual void NativeOnInitialized() override;

private:
    FLevelData LevelData;

    UFUNCTION()
    void OnLevelItemClicked();

    UFUNCTION()
    void OnLevelItemHovered();

    UFUNCTION()
    void OnLevelItemUnovered();
	
};
