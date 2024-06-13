#include "TOPlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "TOWinLoseWidget.h"
#include "TOScopeWidget.h"
#include "Kismet/GameplayStatics.h"

ATOPlayerController::ATOPlayerController(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{
	FlipFlopState = 0;
}

void ATOPlayerController::LimitPlayerMovement(EEndGameState)
{
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);

	bShowMouseCursor = true;
}

void ATOPlayerController::CreateWinLoseWidget(EEndGameState)
{
	auto* GameMode = Cast<ATOGameModeBase>(GetWorld()->GetAuthGameMode());

	WinLoseWidget = CreateWidget<UTOWinLoseWidget>(this, WinLoseWidgetClass);
	WinLoseWidget->SetEndGameStateTextColor(GameMode->RealEndGameState);
	WinLoseWidget->AddToViewport();
	WinLoseWidget->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void ATOPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto* GameMode = Cast<ATOGameModeBase>(GetWorld()->GetAuthGameMode());

	GameMode->OnEndGame.AddDynamic(this, &ThisClass::LimitPlayerMovement);

	GetWorld()->GetTimerManager().SetTimerForNextTick([this, GameMode]
	{
		GameMode->OnEndGame.AddDynamic(this, &ThisClass::CreateWinLoseWidget);
	});

	CreateScopeWidget();
}

void ATOPlayerController::CreateScopeWidget()
{
	ScopeWidget = CreateWidget<UTOScopeWidget>(this, ScopeWidgetClass);
	ScopeWidget->AddToViewport();
	ScopeWidget->SetVisibility(ESlateVisibility::Visible);
}

void ATOPlayerController::SwitchScopeVisibility()
{
	if (FlipFlopState % 2 == 0)
	{
		ScopeWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ScopeWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	++FlipFlopState;
}
