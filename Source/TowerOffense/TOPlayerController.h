#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TOPlayerController.generated.h"

UCLASS()
class TOWEROFFENSE_API ATOPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATOPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void SetPlayerEnabledState(bool SetPlayerEnabled);

	void LimitPlayerMovement();
};
