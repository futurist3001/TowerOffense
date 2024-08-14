#include "PageLevelWidget.h"

#include "ButtonLevelWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "TowerOffense/Generic/LevelSystem.h"

void UPageLevelWidget::InitializePage(int32 MaxButtonsPerPage, int32 TotalLevels)
{
	TotalPages = FMath::CeilToInt(
		static_cast<float>(TotalLevels) / MaxButtonsPerPage); // calculate number of pages
	CurrentPage = 0;

	CreateButtons(0, FMath::Min(MaxButtonsPerPage, TotalLevels)); // fisrt page;
}

void UPageLevelWidget::NextPage()
{
	if (CurrentPage <= TotalPages - 1)
	{
		CurrentPage++;
		PlayAnimationForward(SlideAnimation);
		UpdatePageButtons();
	}
}

void UPageLevelWidget::PreviousPage()
{
	if (CurrentPage > 0)
	{
		CurrentPage--;
		PlayAnimationReverse(SlideAnimation);
		UpdatePageButtons();
	}
}

void UPageLevelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NextButton->OnClicked.AddDynamic(this, &UPageLevelWidget::NextPage);
	PreviousButton->OnClicked.AddDynamic(this, &UPageLevelWidget::PreviousPage);
}

void UPageLevelWidget::CreateButtons(int32 StratIndex, int32 EndIndex)
{
	if (ButtonLevelWidgetClass)
	{
		for (int32 i = StratIndex; i < EndIndex; i++)
		{
			if (i >= 0 && i < EndIndex / 2)
			{
				if (UpperHorizontalBox)
				{
					UButtonLevelWidget* LevelButton =
						CreateWidget<UButtonLevelWidget>(this, ButtonLevelWidgetClass);
					LevelButton->InitializeButton(i + 1);

					LevelButton->OnLevelSelected.AddDynamic(
						this, &UPageLevelWidget::OnLevelSelected);

					UpperHorizontalBox->AddChildToHorizontalBox(LevelButton);
					VerticalBox->AddChildToVerticalBox(UpperHorizontalBox);
				}
			}

			else if (i >= EndIndex / 2 && i < EndIndex)
			{
				if (LowerHorizontalBox)
				{
					UButtonLevelWidget* LevelButton =
						CreateWidget<UButtonLevelWidget>(this, ButtonLevelWidgetClass);
					LevelButton->InitializeButton(i + 1);

					LevelButton->OnLevelSelected.AddDynamic(
						this, &UPageLevelWidget::OnLevelSelected);

					LowerHorizontalBox->AddChildToHorizontalBox(LevelButton);
					VerticalBox->AddChildToVerticalBox(LowerHorizontalBox);
				}
			}
		}
	}
}

void UPageLevelWidget::UpdatePageButtons()
{
	ULevelSystem* LevelSystem = GEngine->GetEngineSubsystem<ULevelSystem>();

	int32 StartIndex = CurrentPage * 10;
	int32 EndIndex = FMath::Min(StartIndex + 10, LevelSystem->Levels.Num());

	UpperHorizontalBox->ClearChildren();
	LowerHorizontalBox->ClearChildren();

	CreateButtons(StartIndex, EndIndex);
}

void UPageLevelWidget::OnLevelSelected(int32 LevelIndex)
{
	ULevelSystem* LevelSystem = GEngine->GetEngineSubsystem<ULevelSystem>();
	LevelSystem->OpenRelativeLevel(GetWorld(), LevelIndex);
}
