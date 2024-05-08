#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "TOGameModeBase.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	Team1 UMETA(DisplayName = "Team 1"),
	Team2 UMETA(DisplayName = "Team 2")
};

UCLASS()
class TOWEROFFENSE_API ATOGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	TArray<AActor*> FoundTowers;
	TArray<AActor*> FoundTanks;

	uint8 bOneIteration : 1;

public:
	ATOGameModeBase();

	void Win();
	void Lose();

private:
	virtual void Tick(float DeltaTime) override;
};