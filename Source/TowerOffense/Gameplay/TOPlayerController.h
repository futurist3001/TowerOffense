#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TOGameModeBase.h"

#include "TOPlayerController.generated.h"

class UTOPreparationWidget;
class UTOScopeWidget;
class UTOWinLoseWidget;

UCLASS()
class TOWEROFFENSE_API ATOPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UTOWinLoseWidget> WinLoseWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UTOScopeWidget> ScopeWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UTOPreparationWidget> PreparationWidgetClass;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTOWinLoseWidget> WinLoseWidget;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTOScopeWidget> ScopeWidget;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTOPreparationWidget> PreparationWidget;

private:
	FTimerHandle TimerHandle;

public:
	UFUNCTION(BlueprintCallable)
	void SwitchScopeVisibility();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void CreateScopeWidget();

	void CreatePreparationWidget();
	void DestroyPreparationWidget();

private:
	UFUNCTION()
	void LimitPlayerMovement(EGamePhase EndGameState); // here parameter only for binding OnEndGame

	UFUNCTION()
	void CreateWinLoseWidget(EGamePhase EndGameState); // here parameter only for binding OnEndGame
};