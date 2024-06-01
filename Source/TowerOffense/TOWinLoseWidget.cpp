#include "TOWinLoseWidget.h"
#include "Components/Button.h"
#include "TOGameModeBase.h"
#include "Kismet/GameplayStatics.h"

UTOWinLoseWidget::UTOWinLoseWidget(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void UTOWinLoseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ATOGameModeBase* TOGameModeBase = Cast<ATOGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	RestartButton->OnClicked.AddDynamic(TOGameModeBase, &ATOGameModeBase::Restart);
	QuitButton->OnClicked.AddDynamic(TOGameModeBase, &ATOGameModeBase::Quit);
}