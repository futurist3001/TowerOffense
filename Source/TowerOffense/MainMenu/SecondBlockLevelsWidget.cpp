#include "SecondBlockLevelsWidget.h"

#include "Components/Button.h"

void USecondBlockLevelsWidget::DoOpenSecondBlockLevels()
{
	for (auto& Level : SecondBlockLevels)
	{
		if (Level.Value && Level.Value->IsPressed())
		{
			OnPressedSecondBlockButton.Broadcast(GetWorld(), Level.Key);
		}
	}
}

void USecondBlockLevelsWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	SecondBlockLevels.Add(11, EleventhLevel);
	SecondBlockLevels.Add(12, TwelfthLevel);
	SecondBlockLevels.Add(13, ThirteenthLevel);
	SecondBlockLevels.Add(14, FourteenthLevel);
	SecondBlockLevels.Add(15, FifteenthLevel);
	SecondBlockLevels.Add(16, SixteenthLevel);
	SecondBlockLevels.Add(17, SeventeenthLevel);
	SecondBlockLevels.Add(18, EighteenthLevel);
	SecondBlockLevels.Add(19, NineteenthLevel);
	SecondBlockLevels.Add(20, TwentiethLevel);
}

void USecondBlockLevelsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (auto& Level : SecondBlockLevels)
	{
		Level.Value->OnPressed.AddDynamic(this, &USecondBlockLevelsWidget::DoOpenSecondBlockLevels);
	}
}
