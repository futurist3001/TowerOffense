#include "TOGameModeBase.h"

ATOGameModeBase::ATOGameModeBase()
{
}

FColor ATOGameModeBase::GetTeamColor(ETeam Team)
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
