#include "TOPlayerController.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TOScopeWidget.h"
#include "TOWinLoseWidget.h"

void ATOPlayerController::SwitchScopeVisibility()
{
	const ESlateVisibility Visibility = ScopeWidget->GetVisibility() != ESlateVisibility::Visible
		? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
	ScopeWidget->SetVisibility(Visibility);
}

void ATOPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CreateScopeWidget();

	auto* GameMode = Cast<ATOGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->OnGamePhaseChanged.AddDynamic(this, &ThisClass::LimitPlayerMovement);
	GameMode->OnGamePhaseChanged.AddDynamic(this, &ThisClass::CreateWinLoseWidget);
}

void ATOPlayerController::CreateScopeWidget()
{
	ScopeWidget = CreateWidget<UTOScopeWidget>(this, ScopeWidgetClass);
	ScopeWidget->AddToViewport();
	ScopeWidget->SetVisibility(ESlateVisibility::Visible);
}

void ATOPlayerController::LimitPlayerMovement(EGamePhase)
{
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);

	bShowMouseCursor = true;
}

void ATOPlayerController::CreateWinLoseWidget(EGamePhase EndGameState)
{
	WinLoseWidget = CreateWidget<UTOWinLoseWidget>(this, WinLoseWidgetClass);
	WinLoseWidget->SetEndGameStateTextColor(EndGameState);
	WinLoseWidget->AddToViewport();
	WinLoseWidget->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}