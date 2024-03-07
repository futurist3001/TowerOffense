#pragma once

#include "CoreMinimal.h"
#include "TurretPawn.h"

#include "TowerPawn.generated.h"

class USphereComponent;

UCLASS()
class TOWEROFFENSE_API ATowerPawn : public ATurretPawn
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(Transient)
	TArray<AActor*> OverllapedActor;

private:
	int8 DoOnce : 1;
	float TimeFire;

public:
	ATowerPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void RotateTurret() override;

	void Fire();

private:
	UFUNCTION()
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

};
