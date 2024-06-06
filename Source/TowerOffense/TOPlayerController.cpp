#include "TOPlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "TOWinLoseWidget.h"
#include "Kismet/GameplayStatics.h"

ATOPlayerController::ATOPlayerController(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{
}

void ATOPlayerController::SetPlayerEnabledState(bool SetPlayerEnabled)
{
	if (APawn* ValidPawn = GetPawn())
	{
		SetPlayerEnabled ? ValidPawn->EnableInput(this) : ValidPawn->DisableInput(this);
	}

	bShowMouseCursor = SetPlayerEnabled;
}

void ATOPlayerController::LimitPlayerMovement(EEndGameState)
{
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this);

	bShowMouseCursor = true;
}

void ATOPlayerController::CreateWinLoseWidget(EEndGameState)
{
	auto* WinLoseWidget = CreateWidget<UTOWinLoseWidget>(this, WinLoseWidgetClass);
	WinLoseWidget->AddToViewport();
	WinLoseWidget->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void ATOPlayerController::BeginPlay()
{
	auto* GameMode = Cast<ATOGameModeBase>(GetWorld()->GetAuthGameMode());

	auto BindingCreateWLW{ [this, GameMode]() {GameMode->OnEndGame.AddDynamic(this, &ATOPlayerController::CreateWinLoseWidget); } };
	GetWorld()->GetTimerManager().SetTimerForNextTick(BindingCreateWLW);
}
