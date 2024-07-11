#include "TOMMGameModeBase.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

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

void ATOMMGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (MMBackSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), MMBackSound);
	}
}
