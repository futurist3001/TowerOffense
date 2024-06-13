#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TOGameModeBase.h"

#include "TOPlayerController.generated.h"

class UTOWinLoseWidget;
class UTOScopeWidget;

UCLASS()
class TOWEROFFENSE_API ATOPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	uint32 FlipFlopState;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UTOWinLoseWidget> WinLoseWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UTOScopeWidget> ScopeWidgetClass;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTOWinLoseWidget> WinLoseWidget;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTOScopeWidget> ScopeWidget;

public:
	ATOPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void SetPlayerEnabledState(bool SetPlayerEnabled);

	UFUNCTION()
	void LimitPlayerMovement(EEndGameState EndGameState); // here parameter only for binding OnEndGame

	UFUNCTION()
	void CreateWinLoseWidget(EEndGameState EndGameState); // here parameter only for binding OnEndGame

protected:
	virtual void BeginPlay() override;

	void CreateScopeWidget();

	UFUNCTION(BlueprintCallable)
	void SwitchScopeVisibility();
};
