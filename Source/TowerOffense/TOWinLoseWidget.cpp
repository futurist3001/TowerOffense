#include "TOWinLoseWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "TOGameModeBase.h"

void UTOWinLoseWidget::SetEndGameStateTextColor(EGamePhase EndGameState)
{
	if (EndGameStateText)
	{
 		const FString RealEndGameStateString = UEnum::GetDisplayValueAsText(EndGameState).ToString();
		EndGameStateText->SetText(FText::FromString(RealEndGameStateString));

		const FColor Color = EndGameState == EGamePhase::Win ? FColor::Green : FColor::Red;
		EndGameStateText->SetColorAndOpacity(FSlateColor(Color));
	}
}

void UTOWinLoseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto* GameMode = GetWorld()->GetAuthGameMode<ATOGameModeBase>();

	RestartButton->OnClicked.AddDynamic(GameMode, &ATOGameModeBase::Restart);
	QuitButton->OnClicked.AddDynamic(GameMode, &ATOGameModeBase::ReturnToMainMenu); // may be think about returning to the main menu
}