#include "TOGameModeBase.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TankPawn.h"
#include "TowerPawn.h"

ATOGameModeBase::ATOGameModeBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	NumberTowers = 0;
	NumberTanks = 0;
}

void ATOGameModeBase::Restart()
{
	UGameplayStatics::OpenLevel(GetWorld(), MapName, true);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());

	GamePhase = EGamePhase::Playing; // ?????????????????????
}

void ATOGameModeBase::Quit()
{
	UKismetSystemLibrary::QuitGame(
		GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void ATOGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GamePhase = EGamePhase::Playing; // ??????????????????

	InitPlayData();
}

void ATOGameModeBase::InitPlayData()
{
#define INIT_PLAY_DATA(Class, Count, Method)                        \
	do {                                                            \
		TArray<AActor*> Actors;                                     \
		UGameplayStatics::GetAllActorsOfClass(this, Class, Actors); \
		Count = Actors.Num();                                       \
		for (AActor* Actor : Actors)                                \
		{                                                           \
			Actor->OnDestroyed.AddDynamic(this, Method);            \
		}                                                           \
	} while (0)

	INIT_PLAY_DATA(ATowerPawn::StaticClass(), NumberTowers, &ATOGameModeBase::TowerDestroyed);
	INIT_PLAY_DATA(ATankPawn::StaticClass(), NumberTanks, &ATOGameModeBase::TankDestroyed);
#undef INIT_PLAY_DATA
}

void ATOGameModeBase::Win()
{
	SetEndGameState(EGamePhase::Win);
}

void ATOGameModeBase::Lose()
{
	SetEndGameState(EGamePhase::Lose);
}

void ATOGameModeBase::SetEndGameState(EGamePhase State)
{
	GamePhase = State;
	OnGamePhaseChanged.Broadcast(GamePhase);
}

void ATOGameModeBase::TankDestroyed(AActor* DestroyedActor)
{
	if (--NumberTanks < 1 && GamePhase == EGamePhase::Playing)
	{
		Lose();
	}
}

void ATOGameModeBase::TowerDestroyed(AActor* DestroyedActor)
{
	if (--NumberTowers < 1 && GamePhase == EGamePhase::Playing)
	{
 		Win();
	}
}