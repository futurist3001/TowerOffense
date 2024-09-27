#include "TowerOffense/Public/Generic/LevelSystem.h"

#include "Kismet/GameplayStatics.h"

void ULevelSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	NumberLevels = 20;

	LoadLevelState();

	if (Levels.Num() == 0)
	{
		for (int i = 0; i < NumberLevels; ++i)
		{
			i == 0 ? Levels.Add(true) : Levels.Add(false);
		}
	}
}

void ULevelSystem::OpenRelativeLevel(const UObject* WorldContextObject, int32 LevelIndex)
{
	for (const auto& Level : Levels)
	{
		if (Levels.IsValidIndex(LevelIndex - 1) && Levels[LevelIndex - 1] == true)
		{
			FString LevelName = FString::Printf(TEXT("Level_%d"), LevelIndex);
			UGameplayStatics::OpenLevel(WorldContextObject, FName(*LevelName), true);

			ActualCurrentLevel = LevelIndex;
		}
	}
}

void ULevelSystem::OpenNextLevel(const UObject* WorldContextObject, int32 NextLevelIndex)
{
	if (Levels.IsValidIndex(NextLevelIndex - 1))
	{
		Levels[NextLevelIndex - 1] = true;
	}
}

void ULevelSystem::ResetLevelAccess()
{
	for (int i = 0; i < Levels.Num(); ++i)
	{
		i == 0 ? Levels[i] = true : Levels[i] = false;
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
		JsonLevel->SetBoolField(TEXT("bIsUnlockedLevel"), Level);

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
				bool IsUnlockedLevel = JsonLevel->GetBoolField(TEXT("bIsUnlockedLevel"));

				Levels.Add(IsUnlockedLevel);
			}
		}
	}
}
