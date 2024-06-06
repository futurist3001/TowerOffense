#include "TOWinLoseWidget.h"
#include "Components/Button.h"
#include "TOGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "TOPlayerController.h"

UTOWinLoseWidget::UTOWinLoseWidget(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void UTOWinLoseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto* GameMode = GetWorld()->GetAuthGameMode<ATOGameModeBase>();

	RestartButton->OnClicked.AddDynamic(GameMode, &ATOGameModeBase::Restart);
	QuitButton->OnClicked.AddDynamic(GameMode, &ATOGameModeBase::Quit);
}