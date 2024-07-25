#pragma once
#include "CoreMinimal.h"
#include "TurretPawn.h"

#include "TankPawn.generated.h"

class UAudioComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UNiagaraSystem;
class USoundBase;
class USpringArmComponent;
struct FHitResult;
struct FInputActionValue;
struct FInputActionInstance;

UCLASS()
class TOWEROFFENSE_API ATankPawn : public ATurretPawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
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

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	TObjectPtr<USceneComponent> RightTankTrack;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	TObjectPtr<USceneComponent> LeftTankTrack;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	TObjectPtr<USceneComponent> LeftTankTrackRotation;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	TObjectPtr<USceneComponent> RightTankTrackRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	TObjectPtr<UNiagaraSystem> MovementEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
	TObjectPtr<USoundBase> MovementSound;

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
	uint8 bPlayedTurretRotationSoundIteration : 1;
	FHitResult ShootingPoint;
	UAudioComponent* MovementAudioComponent;
	
public:
	ATankPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void RotateTurret() override;
	virtual void Fire() override;

	void MoveStarted();
	void MoveTriggeredValue(const FInputActionValue& Value);
	void MoveTriggeredInstance(const FInputActionInstance& Instance);
	void MoveCompleted();

	void Turn(const FInputActionValue& Value);
	void Rotate(const FInputActionValue& Value);
};
