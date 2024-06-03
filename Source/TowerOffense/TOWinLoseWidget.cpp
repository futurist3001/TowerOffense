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

	ATOGameModeBase* TOGameModeBase = Cast<ATOGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	ATOPlayerController* TOPlayerController = Cast<ATOPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	RestartButton->OnClicked.AddDynamic(TOGameModeBase, &ATOGameModeBase::Restart);
	QuitButton->OnClicked.AddDynamic(TOGameModeBase, &ATOGameModeBase::Quit);

	TOPlayerController->LimitPlayerMovement();
}