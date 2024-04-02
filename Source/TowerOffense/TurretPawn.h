#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "TurretPawn.generated.h"

class AProjectile;
class UCapsuleComponent;
struct FInputActionValue;

UCLASS()
class TOWEROFFENSE_API ATurretPawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileActor;

protected:
	UPROPERTY(EditAnywhere, Category = "Base", meta = (GetOptions = "GetBaseMeshMaterialSlotOptions"))
	FName BaseMeshMaterialSlotName;

	UPROPERTY(EditAnywhere, Category = "Base", meta = (GetOptions = "GetBaseMeshMaterialParameterOptions"))
	FName BaseMaterialParameterName;

	UPROPERTY(EditAnywhere, Category = "Base")
	FLinearColor BaseColor;

	UPROPERTY(EditAnywhere, Category = "Turret", meta = (GetOptions = "GetTurretMeshMaterialSlotOptions"))
	FName TurretMeshMaterialSlotName;

	UPROPERTY(EditAnywhere, Category = "Turret", meta = (GetOptions = "GetTurretMeshMaterialParameterOptions"))
	FName TurretMaterialParameterName;

	UPROPERTY(EditAnywhere, Category = "Turret")
	FLinearColor TurretColor;

	UPROPERTY(EditAnywhere, Category = "Turret")
	float TurretRotationSpeed;

	UPROPERTY(Transient)
	UMaterialInstanceDynamic* BaseDynamicMaterialInstance;

	UPROPERTY(Transient)
	UMaterialInstanceDynamic* TurretDynamicMaterialInstance;

	FRotator TargetAngle; // For rotation
	float RotationCurrentTime;

public:
	ATurretPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void RotateTurret();
	virtual void Fire();

private:
	UFUNCTION()
	TArray<FName> GetBaseMeshMaterialSlotOptions() const;

	UFUNCTION()
	TArray<FName> GetTurretMeshMaterialSlotOptions() const;

	static TArray<FName> GetMaterialSlotOptions(const UStaticMeshComponent* InputComponentSlot);

	UFUNCTION()
	TArray<FName> GetBaseMeshMaterialParameterOptions() const;

	UFUNCTION()
	TArray<FName> GetTurretMeshMaterialParameterOptions() const;
	
	static TArray<FName> GetMaterialParameterOptions(
		const UStaticMeshComponent* InputComponentParameter, FName MeshMaterialSlotName);

	void SetMeshMaterial(
		UStaticMeshComponent* MeshComponent, FName MeshMaterialSlotName, FName MaterialParameterName,
		const FLinearColor& Color, UMaterialInstanceDynamic*& DynamicMaterialInstance);

};
