#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "TOMMGameModeBase.generated.h"

UCLASS()
class TOWEROFFENSE_API ATOMMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MapName;

public:
	ATOMMGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void QuitGame();
};
