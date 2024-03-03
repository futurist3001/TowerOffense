#pragma once
#include "CoreMinimal.h"
#include "TurretPawn.h"

#include "TankPawn.generated.h"

struct FHitResult;
struct FInputActionValue;
struct FInputActionInstance;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;

UCLASS()
class TOWEROFFENSE_API ATankPawn : public ATurretPawn
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> TankMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveForwardAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> TurnRightAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float AccelerationDuration;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed;

private:
	FVector MovementVector;
	FVector PreviousMovementVector; // previous pressed button 
	int DoOnce;
	float CurrentTime;
	float CurrentSpeed;
	float SpeedStopGas; // speed after acceleration
	float SpeedStopBraking; // speed after braking
	uint8 bIsStopMoving : 1;
	FHitResult* OutSweepHitResult; // hit for local offset and local rotatiion
	FHitResult HitResult; // hit result for cursor direction

public:
	ATankPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void RotateTurret() override;

	void MoveTriggeredValue(const FInputActionValue& Value);
	void MoveTriggeredInstance(const FInputActionInstance& Instance);
	void MoveCompleted();

	void Turn(const FInputActionValue& Value);
	void Fire(const FInputActionInstance& Instance);
};
