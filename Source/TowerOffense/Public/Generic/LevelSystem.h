#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"

#include "LevelSystem.generated.h"

UCLASS()
class TOWEROFFENSE_API ULevelSystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	TArray<bool> Levels;
	int32 ActualCurrentLevel;

private:
	int32 NumberLevels;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void OpenRelativeLevel(const UObject* WorldContextObject, int32 LevelIndex);

	UFUNCTION()
	void OpenNextLevel(const UObject* WorldContextObject, int32 NextLevelIndex);

	UFUNCTION()
	void ResetLevelAccess();

	void SaveLevelState();
	void LoadLevelState();

	int32 GetNumberLevels() const
	{ 
		return NumberLevels;
	}
};
