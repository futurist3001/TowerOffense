#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"

#include "LevelSystem.generated.h"

USTRUCT(BlueprintType)
struct FLevelData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PreviousLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NextLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsUnlockedLevel;
};

UCLASS()
class TOWEROFFENSE_API ULevelSystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	TMap<int32, FLevelData> Levels;
	int32 ActualPreviousLevel;
	int32 ActualCurrentLevel;
	int32 ActualNextLevel;

private:
	int32 NumberLevels;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION()
	void OpenRelativeLevel(const UObject* WorldContextObject, int32 LevelIndex);

	UFUNCTION()
	void OpenNextLevel(const UObject* WorldContextObject, int32 NextLevelIndex);

	UFUNCTION()
	void ResetLevelAccess();

	int32 GetNumberLevels() const
	{ 
		return NumberLevels;
	}
};
