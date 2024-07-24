#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "FirstBlockLevelsWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnPressedButton, const UObject*, WorldContextObject, int32, LevelIndex);

class UButton;

UCLASS()
class TOWEROFFENSE_API UFirstBlockLevelsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPressedButton OnPressedFirstBlockButton;
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> FirstLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SecondLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ThirdLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> FourthLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> FifthLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SixthLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SeventhLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> EighthLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> NinthLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> TenthLevel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> HomeButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> NextBlockButton;

private:
	TMap<int32, UButton*> FirstBlockLevels;

public:
	UFUNCTION()
	void DoOpenLevel();

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
};
