#include "LevelSystem.h"

#include "Kismet/GameplayStatics.h"

void ULevelSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	NumberLevels = 20;

	LoadLevelState();

	if (Levels.Num() == 0)
	{
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

	SaveLevelState();
}

void ULevelSystem::SaveLevelState()
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	TArray<TSharedPtr<FJsonValue>> JsonLevelsArray;

	for (const auto& Level : Levels)
	{
		TSharedPtr<FJsonObject> JsonLevel = MakeShareable(new FJsonObject);
		JsonLevel->SetNumberField(TEXT("PreviousLevel"), Level.Value.PreviousLevel);
		JsonLevel->SetNumberField(TEXT("CurrentLevel"), Level.Value.CurrentLevel);
		JsonLevel->SetNumberField(TEXT("NextLevel"), Level.Value.NextLevel);
		JsonLevel->SetBoolField(TEXT("bIsUnlockedLevel"), Level.Value.bIsUnlockedLevel);

		TSharedPtr<FJsonValue> JsonValue = MakeShareable(new FJsonValueObject(JsonLevel));
		JsonLevelsArray.Add(JsonValue);
	}

	JsonObject->SetArrayField(TEXT("Levels"), JsonLevelsArray);

	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	FFileHelper::SaveStringToFile(OutputString, *(FPaths::ProjectSavedDir() + TEXT("LevelState.json")));
}

void ULevelSystem::LoadLevelState()
{
	FString JsonString;
	FFileHelper::LoadFileToString(JsonString, *(FPaths::ProjectSavedDir() + TEXT("LevelState.json")));

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		Levels.Empty();

		const TArray<TSharedPtr<FJsonValue>>* JsonLevelsArray;

		if (JsonObject->TryGetArrayField(TEXT("Levels"), JsonLevelsArray))
		{
			for (const TSharedPtr<FJsonValue>& JsonValue : *JsonLevelsArray)
			{
				TSharedPtr<FJsonObject> JsonLevel = JsonValue->AsObject();

				FLevelData LevelData;
				LevelData.PreviousLevel = JsonLevel->GetIntegerField(TEXT("PreviousLevel"));
				LevelData.CurrentLevel = JsonLevel->GetIntegerField(TEXT("CurrentLevel"));
				LevelData.NextLevel = JsonLevel->GetIntegerField(TEXT("NextLevel"));
				LevelData.bIsUnlockedLevel = JsonLevel->GetBoolField(TEXT("bIsUnlockedLevel"));

				Levels.Add(LevelData.CurrentLevel, LevelData);
			}
		}
	}
}
