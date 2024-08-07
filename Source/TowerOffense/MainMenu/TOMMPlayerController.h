#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TOMMPlayerController.generated.h"

class UFirstBlockLevelsWidget;
class USecondBlockLevelsWidget;
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Levels")
	TSubclassOf<USecondBlockLevelsWidget> SecondBlockLevelsWidgetClass;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "Levels")
	TObjectPtr<USecondBlockLevelsWidget> SecondBlockLevelsWidget;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UTOMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTOMainMenuWidget> MainMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
	TObjectPtr<USoundBase> MMBackSound;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void LimitPlayerMovement();

	UFUNCTION()
	void CreateMainMenuWidget();

	UFUNCTION()
	void CreateFirstBlockLevelsWidget();

	UFUNCTION()
	void CreateSecondBlockLevelsWidget();
};
