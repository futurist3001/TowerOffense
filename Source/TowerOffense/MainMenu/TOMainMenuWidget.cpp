#include "TOMainMenuWidget.h"

#include "Components/Button.h"
#include "TOMMGameModeBase.h"
#include "TOMMPlayerController.h"
#include "TowerOffense/Generic/LevelSystem.h"

void UTOMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (MMSlideAnimation)
	{
		PlayAnimationForward(MMSlideAnimation);
	}

	auto* MMGameMode = GetWorld()->GetAuthGameMode<ATOMMGameModeBase>();
	auto* PlayerController = GetWorld()->GetFirstPlayerController<ATOMMPlayerController>();
	ULevelSystem* LevelSystem = GEngine->GetEngineSubsystem<ULevelSystem>();

	StartGameButton->OnClicked.AddDynamic(MMGameMode, &ATOMMGameModeBase::StartGame);
	LevelButton->OnClicked.AddDynamic(PlayerController, &ATOMMPlayerController::CreatePageLevelWidget);
	LevelButton->OnClicked.AddDynamic(this, &UTOMainMenuWidget::DestroyMMWidget);
	ResetLevelAccessButton->OnClicked.AddDynamic(LevelSystem, &ULevelSystem::ResetLevelAccess);
	QuitGameButton->OnClicked.AddDynamic(MMGameMode, &ATOMMGameModeBase::QuitGame);
}

void UTOMainMenuWidget::DestroyMMWidget()
{
	RemoveFromParent();
}
