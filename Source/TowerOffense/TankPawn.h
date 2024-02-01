#pragma once
#include "CoreMinimal.h"
#include "TurretPawn.h"

#include "TankPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

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

public:
	ATankPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Turn(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Fire();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
