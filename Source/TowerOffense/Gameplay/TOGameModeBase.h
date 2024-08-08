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
	Preparation,
	Playing,
	Win,
	Lose
};

class USoundBase;

UCLASS()
class TOWEROFFENSE_API ATOGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamePhaseChanged, EGamePhase, DelEndGameState);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTowerDestroyed, int32, TowersRemain);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTankDestroyed, int32, TanksRemain);

	UPROPERTY(BlueprintAssignable)
	FOnGamePhaseChanged OnGamePhaseChanged;

	FOnTowerDestroyed OnTowerDestroyed;
	FOnTankDestroyed OnTankDestroyed;

	float HandleTime; // For delay preparation
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MapName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MainMenuMapName;

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

	FORCEINLINE void SetGamePhase(EGamePhase Phase)
	{
		GamePhase = Phase;
	}

	int32 GetNumberTowers() const
	{
		return NumberTowers;
	}

	int32 GetNumberTanks() const
	{
		return NumberTanks;
	}

	UFUNCTION()
	void Restart();

	UFUNCTION()
	void ReturnToMainMenu();

	UFUNCTION(Exec, Category = "Levels")
	void OpenRelativeLevelCC(int32 LevelIndex) const; // Console command

	FText GetPreparationText();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

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