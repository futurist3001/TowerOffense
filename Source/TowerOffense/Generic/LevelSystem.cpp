#include "LevelSystem.h"

#include "Kismet/GameplayStatics.h"

void ULevelSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	NumberLevels = 20;

	for (int i = 1; i <= NumberLevels; ++i)
	{
		FLevelData LevelData;

		i == 1 ? LevelData.PreviousLevel = i : LevelData.PreviousLevel = i - 1;
		LevelData.CurrentLevel = i;
		i == NumberLevels ? LevelData.NextLevel = i : LevelData.NextLevel = i + 1;
		i == 1 ? LevelData.bIsUnlockedLevel = true : LevelData.bIsUnlockedLevel = false;

		Levels.Add(i, LevelData);
	}
}

void ULevelSystem::Deinitialize()
{
	Super::Deinitialize();
}

void ULevelSystem::OpenRelativeLevel(const UObject* WorldContextObject, int32 LevelIndex)
{
	for (const auto& Level : Levels)
	{
		if (Level.Key == LevelIndex && Level.Value.bIsUnlockedLevel)
		{
			FString LevelName = FString::Printf(TEXT("Level_%d"), Level.Value.CurrentLevel);
			UGameplayStatics::OpenLevel(WorldContextObject, FName(*LevelName), true);

			ActualPreviousLevel = Level.Value.PreviousLevel;
			ActualCurrentLevel = Level.Value.CurrentLevel;
			ActualNextLevel = Level.Value.NextLevel;
		}
	}
}

void ULevelSystem::OpenNextLevel(const UObject* WorldContextObject, int32 NextLevelIndex)
{
	for (auto& Level : Levels)
	{
		if (Level.Value.CurrentLevel == NextLevelIndex)
		{
			Level.Value.bIsUnlockedLevel = true;
		}
	}
}

void ULevelSystem::ResetLevelAccess()
{
	for (auto& Level : Levels)
	{
		Level.Value.CurrentLevel == 1 ? Level.Value.bIsUnlockedLevel = true :
			Level.Value.bIsUnlockedLevel = false;
	}
}
