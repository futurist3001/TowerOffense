#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndGameState.h"

#include "TOGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndGame, EEndGameState, DelEndGameState);

UENUM(BlueprintType)
enum class ETeam : uint8
{
	Team1 UMETA(DisplayName = "Team 1"),
	Team2 UMETA(DisplayName = "Team 2")
};

/*UENUM(BlueprintType)
enum class EEndGameState : uint8
{
	Win UMETA(DisplayName = "Win"),
	Lose UMETA(DisplayName = "Lose")
};*/

UCLASS()
class TOWEROFFENSE_API ATOGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnEndGame OnEndGame;
	
private:
	UPROPERTY(Transient)
	TArray<AActor*> FoundTowers;

	UPROPERTY(Transient)
	TArray<AActor*> FoundTanks;

	int32 NumberTowers;
	int32 NumberTanks;
	FTimerHandle TimerPlayData;

public:
	ATOGameModeBase();

protected:
	UFUNCTION()
	void TankDestroyed(AActor* DestroyedActor);

	UFUNCTION()
	void TowerDestroyed(AActor* DestroyedActor);

	void InitPlayData();

	void Win();
	void Lose();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};