#include "TOMMGameModeBase.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "FirstBlockLevelsWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TowerOffense/Generic/LevelSystem.h"

ATOMMGameModeBase::ATOMMGameModeBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATOMMGameModeBase::StartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), MapName, true);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());
}

void ATOMMGameModeBase::QuitGame()
{
	UKismetSystemLibrary::QuitGame(
		GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void ATOMMGameModeBase::OpenRelativeLevelCC(int32 LevelIndex) const
{
	ULevelSystem* LevelSystem = GEngine->GetEngineSubsystem<ULevelSystem>();
	LevelSystem->OpenRelativeLevel(GetWorld(), LevelIndex);
}