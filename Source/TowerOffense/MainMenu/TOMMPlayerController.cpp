#include "TOMMPlayerController.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "PageLevelWidget.h"
#include "Kismet/GameplayStatics.h"
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

void ATOMMPlayerController::CreatePageLevelWidget()
{
	if (PageLevelClass)
	{
		ULevelSystem* LevelSystem = GEngine->GetEngineSubsystem<ULevelSystem>();

		PageLevelWidget = CreateWidget<UPageLevelWidget>(this, PageLevelClass);
		PageLevelWidget->InitializePage(10, LevelSystem->GetNumberLevels());
		PageLevelWidget->AddToViewport();
		PageLevelWidget->SetVisibility(ESlateVisibility::Visible);
		PageLevelWidget->PlayAnimationReverse(PageLevelWidget->InitializeAnimation);
	}
}
