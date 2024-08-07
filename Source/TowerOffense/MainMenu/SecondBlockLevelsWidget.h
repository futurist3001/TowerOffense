#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FirstBlockLevelsWidget.h"

#include "SecondBlockLevelsWidget.generated.h"

UCLASS()
class TOWEROFFENSE_API USecondBlockLevelsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPressedButton OnPressedSecondBlockButton;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> EleventhLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> TwelfthLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ThirteenthLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> FourteenthLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> FifteenthLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SixteenthLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SeventeenthLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> EighteenthLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> NineteenthLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> TwentiethLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> HomeButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> PreviousBlockButton;

private:
	TMap<int32, UButton*> SecondBlockLevels;

public:
	UFUNCTION()
	void DoOpenSecondBlockLevels();

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
};
