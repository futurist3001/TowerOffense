#include "TOMMPlayerController.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "PageLevelWidget.h"
//#include "FirstBlockLevelsWidget.h"
#include "Kismet/GameplayStatics.h"
//#include "SecondBlockLevelsWidget.h"
#include "TOMainMenuWidget.h"
#include "TowerOffense/Generic/LevelSystem.h"

void ATOMMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (MMBackSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), MMBackSound);
	}

	LimitPlayerMovement();

	CreateMainMenuWidget();
	//CreateFirstBlockLevelsWidget();
	//CreateSecondBlockLevelsWidget();
	//CreatePageLevelWidget();
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

/*void ATOMMPlayerController::CreateFirstBlockLevelsWidget()
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

void ATOMMPlayerController::CreateSecondBlockLevelsWidget()
{
	if (SecondBlockLevelsWidgetClass)
	{
		SecondBlockLevelsWidget = CreateWidget<USecondBlockLevelsWidget>(this, SecondBlockLevelsWidgetClass);
		SecondBlockLevelsWidget->AddToViewport();
		SecondBlockLevelsWidget->SetVisibility(ESlateVisibility::Visible);

		ULevelSystem* LevelSystem = GEngine->GetEngineSubsystem<ULevelSystem>();
		SecondBlockLevelsWidget->OnPressedSecondBlockButton.AddDynamic(LevelSystem, &ULevelSystem::OpenRelativeLevel);
	}
}*/

void ATOMMPlayerController::CreatePageLevelWidget()
{
	if (PageLevelClass)
	{
		ULevelSystem* LevelSystem = GEngine->GetEngineSubsystem<ULevelSystem>();

		PageLevelWidget = CreateWidget<UPageLevelWidget>(this, PageLevelClass);
		PageLevelWidget->InitializePage(10, LevelSystem->Levels.Num());
		PageLevelWidget->AddToViewport();
		PageLevelWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
