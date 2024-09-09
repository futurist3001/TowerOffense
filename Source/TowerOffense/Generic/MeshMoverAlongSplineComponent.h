#pragma once

#include "CoreMinimal.h"

#include "MeshMoverAlongSplineComponent.generated.h"

class USplineComponent;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWEROFFENSE_API UMeshMoverAlongSplineComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float SplineDuration;

protected:
	UPROPERTY(EditAnywhere)
	float StartAtProgress;

	UPROPERTY(BlueprintReadWrite)
	USplineComponent* SplineComponent;
	
private:
	float Timer;
	float SplineProgress;

public:
	UMeshMoverAlongSplineComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void TickComponent(
		float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetSpline(USplineComponent* InSpline);
	
	UFUNCTION(BlueprintCallable)
	void SetStartSplinePosition();
};
