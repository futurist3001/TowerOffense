#include "MeshMoverAlongSplineComponent.h"

#include "Components/SplineComponent.h"

UMeshMoverAlongSplineComponent::UMeshMoverAlongSplineComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;

	Timer = 0;
	bIsPlayed = false;
}

void UMeshMoverAlongSplineComponent::SetSpline(USplineComponent* InSpline)
{
	SplineComponent = InSpline;
}

void UMeshMoverAlongSplineComponent::SetStartSplinePosition()
{
	SetWorldLocation(SplineComponent->GetLocationAtDistanceAlongSpline(
		SplineComponent->GetSplineLength() * StartAtProgress, ESplineCoordinateSpace::World));
}

void UMeshMoverAlongSplineComponent::TickComponent(
	float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (SplineComponent && bIsPlayed)
	{
		Timer += DeltaTime;

		if (Timer > SplineDuration)
		{
			Timer = 0;
		}

		SplineProgress = SplineComponent->GetSplineLength() * (Timer / SplineDuration + StartAtProgress);

		if (SplineProgress > SplineComponent->GetSplineLength())
		{
			SplineProgress = SplineProgress - SplineComponent->GetSplineLength();
		}

		SetWorldLocation(SplineComponent->GetLocationAtDistanceAlongSpline(
			SplineProgress, ESplineCoordinateSpace::World));
	}
}
