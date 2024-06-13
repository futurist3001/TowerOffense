#include "TOWinLoseWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "TOPlayerController.h"
#include "TOGameModeBase.h"

UTOWinLoseWidget::UTOWinLoseWidget(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void UTOWinLoseWidget::SetEndGameStateTextColor(EEndGameState EndGameState)
{
	if (EndGameStateText)
	{
		auto* GameMode = GetWorld()->GetAuthGameMode<ATOGameModeBase>();
 		FString RealEndGameStateString = UEnum::GetDisplayValueAsText(GameMode->RealEndGameState).ToString();
		EndGameStateText->SetText(FText::FromString(RealEndGameStateString));

		if (GameMode->RealEndGameState == EEndGameState::Win)
		{
			EndGameStateText->SetColorAndOpacity(FSlateColor(FColor::Green));
		}
		else
		{
			EndGameStateText->SetColorAndOpacity(FSlateColor(FColor::Red));
		}
	}
}

void UTOWinLoseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto* GameMode = GetWorld()->GetAuthGameMode<ATOGameModeBase>();

	RestartButton->OnClicked.AddDynamic(GameMode, &ATOGameModeBase::Restart);
	QuitButton->OnClicked.AddDynamic(GameMode, &ATOGameModeBase::Quit);
}