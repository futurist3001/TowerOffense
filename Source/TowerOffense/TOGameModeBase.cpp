#include "TOGameModeBase.h"
#include "EngineUtils.h"
#include "TowerPawn.h"
#include "TankPawn.h"
#include "Kismet/GameplayStatics.h"

ATOGameModeBase::ATOGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	//bOneIteration = false;
}

void ATOGameModeBase::Win()
{
	//WinLoseState = "Win";

	//UKismetSystemLibrary::PrintString(
		//GetWorld(), WinLoseState, true, false, FColor::Green, 5.f);

	OnEndGame.Broadcast(EEndGameState::Win);
}

void ATOGameModeBase::Lose()
{
	//WinLoseState = "Lose";

	//UKismetSystemLibrary::PrintString(
		//GetWorld(), WinLoseState, true, false, FColor::Red, 5.f);

	OnEndGame.Broadcast(EEndGameState::Lose);
}

void ATOGameModeBase::HandleEndGameState(EEndGameState ParameterEndGameState)
{
	switch (ParameterEndGameState)
	{
		case EEndGameState::Lose:
		{
			EndGameState = EEndGameState::Lose;
		}

		case EEndGameState::Win:
		{
			EndGameState = EEndGameState::Win;
		}

		default:
			EndGameState = EEndGameState::Win;

		break;
	}
}

void ATOGameModeBase::TankDestroyed(AActor* DestroyedActor)
{
	if (NumberTanks > 0)
	{
		--NumberTanks;
	}
	else
	{
		Lose();
	}
}

void ATOGameModeBase::TowerDestroyed(AActor* DestroyedActor)
{
	if (NumberTowers > 0)
	{
		--NumberTowers;
	}
	else
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

	OnEndGame.AddDynamic(this, &ATOGameModeBase::HandleEndGameState);

	GetWorldTimerManager().SetTimer(TimerPlayData, this, &ATOGameModeBase::InitPlayData, 2.f, true);
}

void ATOGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*UGameplayStatics::GetAllActorsOfClass(
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
	}*/
}
