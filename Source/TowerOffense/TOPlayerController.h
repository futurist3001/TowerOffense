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
	UFUNCTION(BlueprintCallable)
	void SwitchScopeVisibility();

protected:
	virtual void BeginPlay() override;

	void CreateScopeWidget();

private:
	UFUNCTION()
	void LimitPlayerMovement(EGamePhase EndGameState); // here parameter only for binding OnEndGame

	UFUNCTION()
	void CreateWinLoseWidget(EGamePhase EndGameState); // here parameter only for binding OnEndGame
};
