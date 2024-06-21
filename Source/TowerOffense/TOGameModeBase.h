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

UENUM(BlueprintType)
enum class EGamePhase : uint8
{
	Playing,
	Win,
	Lose
};

UCLASS()
class TOWEROFFENSE_API ATOGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamePhaseChanged, EGamePhase, DelEndGameState);
	UPROPERTY(BlueprintAssignable)
	FOnGamePhaseChanged OnGamePhaseChanged;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MapName;

	UPROPERTY(BlueprintReadOnly)
	EGamePhase GamePhase;

private:
	int32 NumberTowers;
	int32 NumberTanks;

public:
	ATOGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	FORCEINLINE EGamePhase GetGamePhase() const
	{
		return GamePhase;
	}

	UFUNCTION()
	void Restart();

	UFUNCTION()
	void Quit();

protected:
	virtual void BeginPlay() override;

	void InitPlayData();
	void Win();
	void Lose();

	void SetEndGameState(EGamePhase State);

private:
	UFUNCTION()
	void TankDestroyed(AActor* DestroyedActor);

	UFUNCTION()
	void TowerDestroyed(AActor* DestroyedActor);
};