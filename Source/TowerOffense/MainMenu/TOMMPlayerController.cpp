#include "TOMMPlayerController.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "FirstBlockLevelsWidget.h"
#include "TOMainMenuWidget.h"
#include "TowerOffense/Generic/LevelSystem.h"

void ATOMMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	LimitPlayerMovement();

	//CreateMainMenuWidget();
	CreateFirstBlockLevelsWidget();
}

void ATOMMPlayerController::LimitPlayerMovement()
{
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);

	bShowMouseCursor = true;
}

void ATOMMPlayerController::CreateMainMenuWidget()
{
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UTOMainMenuWidget>(this, MainMenuWidgetClass);
		MainMenuWidget->AddToViewport();
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ATOMMPlayerController::CreateFirstBlockLevelsWidget()
{
	if (FirstBlockLevelsWidgetClass)
	{
		FirstBlockLevelsWidget = CreateWidget<UFirstBlockLevelsWidget>(this, FirstBlockLevelsWidgetClass);
		FirstBlockLevelsWidget->AddToViewport();
		FirstBlockLevelsWidget->SetVisibility(ESlateVisibility::Visible);

		ULevelSystem* LevelSystem = GEngine->GetEngineSubsystem<ULevelSystem>();
		FirstBlockLevelsWidget->OnPressedFirstBlockButton.AddDynamic(LevelSystem, &ULevelSystem::OpenRelativeLevel);
	}
}
