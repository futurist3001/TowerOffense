#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TOGameModeBase.h"

#include "MyBlueprintFunctionLibrary.generated.h"

UCLASS()
class TOWEROFFENSE_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "MyBPFunctionLibrary")
	static FColor GetTeamColor(ETeam Team);
};
