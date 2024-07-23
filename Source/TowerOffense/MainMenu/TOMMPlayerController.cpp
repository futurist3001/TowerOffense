#include "TOMMPlayerController.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "TOMainMenuWidget.h"

void ATOMMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CreateMainMenuWidget();
}

void ATOMMPlayerController::LimitPlayerMovement()
{
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);

	bShowMouseCursor = true;
}

void ATOMMPlayerController::CreateMainMenuWidget()
{
	LimitPlayerMovement();

	MainMenuWidget = CreateWidget<UTOMainMenuWidget>(this, MainMenuWidgetClass);
	MainMenuWidget->AddToViewport();
	MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
}
