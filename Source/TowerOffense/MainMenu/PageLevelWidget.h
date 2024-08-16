#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "PageLevelWidget.generated.h"

class UButton;
class UButtonLevelWidget;
class UHorizontalBox;
class UVerticalBox;

UCLASS()
class TOWEROFFENSE_API UPageLevelWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox;

	TObjectPtr<UVerticalBox> CopyVerticalBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> UpperHorizontalBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> LowerHorizontalBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UButtonLevelWidget> ButtonLevelWidgetClass;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> FirstPageSlideAnimation;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> SecondPageSlideAnimation;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> PreviousButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> NextButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> HomeButton;

	int32 CurrentPage;
	int32 TotalPages;

public:
	UFUNCTION()
	void InitializePage(int32 MaxButtonsPerPage, int32 TotalLevels);

	UFUNCTION()
	void NextPage();

	UFUNCTION()
	void PreviousPage();

protected:
	virtual void NativeConstruct() override;

private:
	void CreateButtons(int32 StartIndex, int32 EndIndex);

	void UpdatePageButtons();

	UFUNCTION()
	void OnLevelSelected(int32 LevelIndex);

	UFUNCTION()
	void DestroyPageLevelWidget();
};
