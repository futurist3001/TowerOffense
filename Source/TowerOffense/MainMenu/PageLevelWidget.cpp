#include "PageLevelWidget.h"

#include "ButtonLevelWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "TOMMPlayerController.h"
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
	if (CurrentPage < TotalPages - 1)
	{
		CurrentPage++;

		if (SecondPageSlideAnimation)
		{
			PlayAnimationReverse(SecondPageSlideAnimation);
		}

		UpdatePageButtons();
	}
}

void UPageLevelWidget::PreviousPage()
{
	if (CurrentPage > 0)
	{
		CurrentPage--;

		if (FirstPageSlideAnimation)
		{
			PlayAnimationReverse(FirstPageSlideAnimation);
		}

		UpdatePageButtons();
	}
}

void UPageLevelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto* PlayerController = GetWorld()->GetFirstPlayerController<ATOMMPlayerController>();

	CopyVerticalBox = VerticalBox;

	NextButton->OnClicked.AddDynamic(this, &UPageLevelWidget::NextPage);
	PreviousButton->OnClicked.AddDynamic(this, &UPageLevelWidget::PreviousPage);
	HomeButton->OnClicked.AddDynamic(PlayerController, &ATOMMPlayerController::CreateMainMenuWidget);
	HomeButton->OnClicked.AddDynamic(this, &UPageLevelWidget::DestroyPageLevelWidget);
}

void UPageLevelWidget::CreateButtons(int32 StartIndex, int32 EndIndex)
{
	if (ButtonLevelWidgetClass)
	{
		for (int32 i = StartIndex; i < EndIndex; i++)
		{
			if (i >= StartIndex && i < EndIndex - 5 && UpperHorizontalBox) // subtract 5 because in every row 5 buttons
			{
					UButtonLevelWidget* LevelButton =
						CreateWidget<UButtonLevelWidget>(this, ButtonLevelWidgetClass);
					LevelButton->InitializeButton(i + 1);

					LevelButton->OnLevelSelected.AddDynamic(
						this, &UPageLevelWidget::OnLevelSelected);

					UpperHorizontalBox->AddChildToHorizontalBox(LevelButton);
					VerticalBox->AddChildToVerticalBox(UpperHorizontalBox);
			}

			else if (i >= EndIndex - 5 && i < EndIndex && LowerHorizontalBox) // subtract 5 because in every row 5 buttons
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

void UPageLevelWidget::UpdatePageButtons()
{
	ULevelSystem* LevelSystem = GEngine->GetEngineSubsystem<ULevelSystem>();

	int32 StartIndex = CurrentPage * 10;
	int32 EndIndex = FMath::Min(StartIndex + 10, LevelSystem->Levels.Num());

	UpperHorizontalBox->ClearChildren();
	LowerHorizontalBox->ClearChildren();

	VerticalBox = CopyVerticalBox;

	CreateButtons(StartIndex, EndIndex);
}

void UPageLevelWidget::OnLevelSelected(int32 LevelIndex)
{
	ULevelSystem* LevelSystem = GEngine->GetEngineSubsystem<ULevelSystem>();
	LevelSystem->OpenRelativeLevel(GetWorld(), LevelIndex);
}

void UPageLevelWidget::DestroyPageLevelWidget()
{
	RemoveFromParent();
}
