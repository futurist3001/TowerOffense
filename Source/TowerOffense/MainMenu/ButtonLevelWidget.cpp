#include "ButtonLevelWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UButtonLevelWidget::InitializeButton(int32 LevelIndex)
{
	CurrentLevelIndex = LevelIndex;

	if (LevelIndex && TextLevel)
	{
		TextLevel->SetText(FText::AsNumber(LevelIndex));
	}
}

void UButtonLevelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (LevelButton && !LevelButton->OnClicked.IsBound())
	{
		LevelButton->OnClicked.AddDynamic(
			this, &UButtonLevelWidget::HandleButtonClicked);
	}
}

void UButtonLevelWidget::HandleButtonClicked()
{
	OnLevelSelected.Broadcast(CurrentLevelIndex);
}
