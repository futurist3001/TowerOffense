#include "TowerOffense/Public/Generic/MyBlueprintFunctionLibrary.h"

FColor UMyBlueprintFunctionLibrary::GetTeamColor(ETeam Team)
{
	switch (Team)
	{
		case ETeam::Team1:
			return FColor::Green;
		case ETeam::Team2:
			return FColor::Red;
		default:
			return FColor::Blue;
	}
}
