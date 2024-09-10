#include "UActorMoverComponent.h"

#include "TowerOffense/Gameplay/TOGameModeBase.h"

UUActorMoverComponent::UUActorMoverComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;

	Reverse = 1;
	DistanceToMove = 0;
	CurDistance = 0;
	InterpFunc = EInterpolation::InterpSinInOut;
	bIsPlayed = false;
}

void UUActorMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	Parent = GetOwner();
	StartLocation = Parent->GetActorLocation();
	TargetLocation = DirectionToMove;
	DistanceToMove = DirectionToMove.Length();
}

void UUActorMoverComponent::TickComponent(
	float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsPlayed)
	{
		const float Alpha = CurDistance / DistanceToMove;
		CurDistance += DeltaTime * Speed * Reverse;

		if (DistanceToMove <= CurDistance || CurDistance <= 0)
		{
			Reverse *= -1;
		}

		switch (InterpFunc)
		{
		case EInterpolation::InterpSinInOut:
			Parent->SetActorLocation(FMath::InterpSinInOut(StartLocation, TargetLocation, Alpha));
			break;

		case EInterpolation::InterpSinIn:
			Parent->SetActorLocation(FMath::InterpSinIn(StartLocation, TargetLocation, Alpha));
			break;

		case::EInterpolation::InterpSinOut:
			Parent->SetActorLocation(FMath::InterpSinOut(StartLocation, TargetLocation, Alpha));
			break;
		}
	}
}

