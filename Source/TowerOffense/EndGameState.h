#pragma once

#include "CoreMinimal.h"

#include "EndGameState.generated.h"


UENUM(BlueprintType)
enum class EEndGameState : uint8
{
	Win,
	Lose
};