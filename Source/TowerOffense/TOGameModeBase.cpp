#include "TOGameModeBase.h"
#include "EngineUtils.h"
#include "TowerPawn.h"
#include "TankPawn.h"
#include "Kismet/GameplayStatics.h"

ATOGameModeBase::ATOGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	bOneIteration = false;
}

void ATOGameModeBase::Win()
{
	UKismetSystemLibrary::PrintString(
		GetWorld(), "Win", true, false, FColor::Green, 5.f);
}

void ATOGameModeBase::Lose()
{
	UKismetSystemLibrary::PrintString(
		GetWorld(), "Lose", true, false, FColor::Red, 5.f);
}

void ATOGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(), ATowerPawn::StaticClass(), FoundTowers);

	if (FoundTowers.Num() == 0 && !bOneIteration)
	{
		Win();
		bOneIteration = true;
	}

	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(), ATankPawn::StaticClass(), FoundTanks);

	if (FoundTanks.Num() == 0 && !bOneIteration)
	{
		Lose();
		bOneIteration = true;
	}
}
