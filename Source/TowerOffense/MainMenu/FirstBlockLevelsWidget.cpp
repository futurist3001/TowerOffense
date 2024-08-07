#include "FirstBlockLevelsWidget.h"

#include "Components/Button.h"

void UFirstBlockLevelsWidget::DoOpenFirtsBlockLevels()
{
	for (auto& Level : FirstBlockLevels)
	{
		if (Level.Value && Level.Value->IsPressed())
		{
			OnPressedFirstBlockButton.Broadcast(GetWorld(), Level.Key);
		}
	}
}

void UFirstBlockLevelsWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	FirstBlockLevels.Add(1, FirstLevel);
	FirstBlockLevels.Add(2, SecondLevel);
	FirstBlockLevels.Add(3, ThirdLevel);
	FirstBlockLevels.Add(4, FourthLevel);
	FirstBlockLevels.Add(5, FifthLevel);
	FirstBlockLevels.Add(6, SixthLevel);
	FirstBlockLevels.Add(7, SeventhLevel);
	FirstBlockLevels.Add(8, EighthLevel);
	FirstBlockLevels.Add(9, NinthLevel);
	FirstBlockLevels.Add(10, TenthLevel);
}

void UFirstBlockLevelsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (auto& Level : FirstBlockLevels)
	{
		Level.Value->OnPressed.AddDynamic(this, &UFirstBlockLevelsWidget::DoOpenFirtsBlockLevels);
	}
}
