#pragma once
#include "CoreMinimal.h"
#include "TurretPawn.h"

#include "TankPawn.generated.h"

class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
struct FHitResult;
struct FInputActionValue;
struct FInputActionInstance;

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
	TObjectPtr<UInputAction> RotateTurretAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float AccelerationDuration;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed;

private:
	FVector MovementVector;
	FVector PreviousMovementVector; // previous pressed button
	float CurrentTime;
	float CurrentSpeed;
	float SpeedStopGas; // speed after acceleration
	float SpeedStopBraking; // speed after braking
	float YawCameraRotator;
	float YawTurnRotator;
	uint8 bIsStopMoving : 1;
	uint8 bReverseAttempt : 1;
	FHitResult ShootingPoint;

public:
	ATankPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void RotateTurret() override;
	virtual void Fire() override;

	void MoveTriggeredValue(const FInputActionValue& Value);
	void MoveTriggeredInstance(const FInputActionInstance& Instance);
	void MoveCompleted();

	void Turn(const FInputActionValue& Value);
	void Rotate(const FInputActionValue& Value);
};
