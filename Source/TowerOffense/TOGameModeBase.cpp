#include "TOGameModeBase.h"
#include "EngineUtils.h"
#include "TowerPawn.h"
#include "TankPawn.h"
#include "Kismet/GameplayStatics.h"

ATOGameModeBase::ATOGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATOGameModeBase::Win()
{
	OnEndGame.Broadcast(EEndGameState::Win);
}

void ATOGameModeBase::Lose()
{
	OnEndGame.Broadcast(EEndGameState::Lose);
}

void ATOGameModeBase::TankDestroyed(AActor* DestroyedActor)
{
	if (NumberTanks > 0)
	{
		--NumberTanks;
	}

	if (NumberTanks <= 0)
	{
		Lose();
	}
}

void ATOGameModeBase::TowerDestroyed(AActor* DestroyedActor)
{
    if (NumberTowers > 0)
	{
		--NumberTowers;

		//UKismetSystemLibrary::PrintString(this, "Destroyed Tower", true, false, FColor::Black, 1.f);
	}

	if (NumberTowers <= 0)
	{
 		Win();
	}
}

void ATOGameModeBase::InitPlayData()
{
	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(), ATowerPawn::StaticClass(), FoundTowers);

	NumberTowers = FoundTowers.Num();

	for (const auto& FoundTower : FoundTowers)
	{
		FoundTower->OnDestroyed.AddDynamic(this, &ATOGameModeBase::TowerDestroyed);
	}

	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(), ATankPawn::StaticClass(), FoundTanks);

	NumberTanks = FoundTanks.Num();

	for (const auto& FoundTank : FoundTanks)
	{
		FoundTank->OnDestroyed.AddDynamic(this, &ATOGameModeBase::TankDestroyed);
	}
}

void ATOGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//GetWorldTimerManager().SetTimer(TimerPlayData, this, &ATOGameModeBase::InitPlayData, 2.f, true);
	InitPlayData();
}

void ATOGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
