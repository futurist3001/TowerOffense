#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ButtonLevelWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class TOWEROFFENSE_API UButtonLevelWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelSelected, int32, LevelIndex);
	FOnLevelSelected OnLevelSelected;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> LevelButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextLevel;

private:
	int32 CurrentLevelIndex;

public:
	void InitializeButton(int32 LevelIndex);

	int32 GetCurrentLevelIndex() const
	{
		return CurrentLevelIndex;
	}

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void HandleButtonClicked();
};
