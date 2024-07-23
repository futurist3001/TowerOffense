#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"

#include "LevelSystem.generated.h"

UCLASS()
class TOWEROFFENSE_API ULevelSystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	TArray<int32> Levels;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void OpenRelativeLevel(const UObject* WorldContextObject, int32 LevelIndex) const;
};
