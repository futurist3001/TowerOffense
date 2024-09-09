#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "UActorMoverComponent.generated.h"

UENUM(BlueprintType)
enum class EInterpolation : uint8
{
	InterpSinInOut,
	InterpSinIn,
	InterpSinOut,
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWEROFFENSE_API UUActorMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FVector DirectionToMove;

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	EInterpolation InterpFunc;

private:
	UPROPERTY(Transient)
	AActor* Parent;

	FVector StartLocation;
	FVector TargetLocation;

	float DistanceToMove;
	float CurDistance;
	float Reverse;

public:
	UUActorMoverComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(
		float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
