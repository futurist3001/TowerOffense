#include "LevelSystem.h"

#include "Kismet/GameplayStatics.h"

void ULevelSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	for (int i = 0; i < 20; ++i) // fill array with 20 levels
	{
		Levels.Add(i + 1);
	}
}

void ULevelSystem::Deinitialize()
{
	Super::Deinitialize();
}

void ULevelSystem::OpenRelativeLevel(const UObject* WorldContextObject, int32 LevelIndex)
{
	if (Levels.IsValidIndex(LevelIndex))
	{
		FString LevelName = FString::Printf(TEXT("Level_%d"), LevelIndex);
		UGameplayStatics::OpenLevel(WorldContextObject, FName(*LevelName), true);

		CurrentLevel = LevelIndex;
	}
}

int32 ULevelSystem::GetCurrentLevel() const
{
	return CurrentLevel;
}