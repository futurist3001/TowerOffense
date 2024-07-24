#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TOMMPlayerController.generated.h"

class UFirstBlockLevelsWidget;
class UTOMainMenuWidget;

UCLASS()
class TOWEROFFENSE_API ATOMMPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Levels")
	TSubclassOf<UFirstBlockLevelsWidget> FirstBlockLevelsWidgetClass;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "Levels")
	TObjectPtr<UFirstBlockLevelsWidget> FirstBlockLevelsWidget;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UTOMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTOMainMenuWidget> MainMenuWidget;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void LimitPlayerMovement();

	UFUNCTION()
	void CreateMainMenuWidget();

	UFUNCTION()
	void CreateFirstBlockLevelsWidget();
};
