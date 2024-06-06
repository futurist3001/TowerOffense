#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TOGameModeBase.h"

#include "TOPlayerController.generated.h"

class UTOWinLoseWidget;

UCLASS()
class TOWEROFFENSE_API ATOPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UTOWinLoseWidget> WinLoseWidgetClass;

public:
	ATOPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void SetPlayerEnabledState(bool SetPlayerEnabled);

	UFUNCTION()
	void LimitPlayerMovement(EEndGameState EndGameState); // here parameter only for binding OnEndGame

	UFUNCTION()
	void CreateWinLoseWidget(EEndGameState EndGameState); // here parameter only for binding OnEndGame

protected:
	virtual void BeginPlay() override;
};
