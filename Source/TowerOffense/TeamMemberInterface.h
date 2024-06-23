#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "TeamMemberInterface.generated.h"

enum class EGamePhase : uint8;

UINTERFACE(MinimalAPI)
class UTeamMemberInterface : public UInterface
{
	GENERATED_BODY()
};

class TOWEROFFENSE_API ITeamMemberInterface
{
	GENERATED_BODY()

public:
	virtual EGamePhase GetGamePhase() const = 0;
	virtual void SetGamePhase(EGamePhase Phase) = 0;
};
