#include "TowerOffense/Public/MainMenu/UI/TOMainMenuWidget.h"

#include "Components/Button.h"
#include "TowerOffense/Public/MainMenu/ModeControl/TOMMGameModeBase.h"
#include "TowerOffense/Public/MainMenu/ModeControl/TOMMPlayerController.h"
#include "TowerOffense/Public/Generic/LevelSystem.h"

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
