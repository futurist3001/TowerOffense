#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "InterfaceTeamMember.generated.h"

UINTERFACE()
class UInterfaceTeamMember : public UInterface
{
	GENERATED_BODY()
};

class IInterfaceTeamMember
{
	GENERATED_BODY()

public:
	virtual EGamePhase GetGamePhase() const = 0;
};