#include "TOGameModeBase.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TankPawn.h"
#include "TowerPawn.h"
#include "TowerOffense/Generic/LevelSystem.h"

ATOGameModeBase::ATOGameModeBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	NumberTowers = 0;
	NumberTanks = 0;
}

void ATOGameModeBase::Restart()
{
	UGameplayStatics::OpenLevel(GetWorld(), MapName, true);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());

	GamePhase = EGamePhase::Playing;
}

void ATOGameModeBase::ReturnToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), MainMenuMapName, true);
}

void ATOGameModeBase::OpenRelativeLevelCC(int32 LevelIndex) const
{
	ULevelSystem* LevelSystem = GEngine->GetEngineSubsystem<ULevelSystem>();
	LevelSystem->OpenRelativeLevel(GetWorld(), LevelIndex);
}

FText ATOGameModeBase::GetPreparationText()
{
	if (HandleTime < 1.f)
	{
		return FText::FromString(TEXT("3"));
	}

	else if (HandleTime >= 1.f && HandleTime < 2.f)
	{
		return FText::FromString(TEXT("2"));
	}

	else if (HandleTime >= 2.f && HandleTime < 3.f)
	{
		return FText::FromString(TEXT("1"));
	}

	else if (HandleTime > 3.f)
	{
		GamePhase = EGamePhase::Playing;

		return FText::FromString(TEXT("Play!"));
	}

	return FText();
}

void ATOGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GamePhase = EGamePhase::Preparation;

	InitPlayData();

	ULevelSystem* LevelSystem = GEngine->GetEngineSubsystem<ULevelSystem>();


	UKismetSystemLibrary::PrintString(
		this, FString::Printf(TEXT("Current Level: %d"), LevelSystem->GetCurrentLevel()), true, false, FColor::Purple, 4.f);
}

void ATOGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleTime += DeltaTime;
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

	OnTankDestroyed.Broadcast(NumberTanks);
}

void ATOGameModeBase::TowerDestroyed(AActor* DestroyedActor)
{
 	if (--NumberTowers < 1 && GamePhase == EGamePhase::Playing)
	{
 		Win();
	}

	OnTowerDestroyed.Broadcast(NumberTowers);
}