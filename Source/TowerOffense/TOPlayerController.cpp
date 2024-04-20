#include "TOPlayerController.h"

ATOPlayerController::ATOPlayerController(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{
}

void ATOPlayerController::SetPlayerEnabledState(bool SetPlayerEnabled)
{
	if (SetPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = SetPlayerEnabled;
}
