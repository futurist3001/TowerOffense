#pragma once

#include "CoreMinimal.h"
#include "LegacyCameraShake.h"

#include "TOCameraShake.generated.h"

UCLASS()
class TOWEROFFENSE_API UTOCameraShake : public ULegacyCameraShake
{
	GENERATED_BODY()

public:
	UTOCameraShake(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
