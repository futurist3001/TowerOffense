#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "TurretPawn.generated.h"

class UCapsuleComponent;

UCLASS()
class TOWEROFFENSE_API ATurretPawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> ProjectileSpawnPoint;

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

protected:
	UPROPERTY()
	UMaterialInstanceDynamic* BaseDynamicMaterialInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* TurretDynamicMaterialInstance;

public:
	ATurretPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	//virtual void PostInitializeComponents() override;
	virtual void OnConstruction(const FTransform& Transform) override;

private:
	UFUNCTION()
	TArray<FName> GetBaseMeshMaterialSlotOptions() const;

	UFUNCTION()
	TArray<FName> GetTurretMeshMaterialSlotOptions() const;

	TArray<FName> GetMaterialSlotOptions(UStaticMeshComponent* InputComponentSlot) const;

	UFUNCTION()
	TArray<FName> GetBaseMeshMaterialParameterOptions() const;

	UFUNCTION()
	TArray<FName> GetTurretMeshMaterialParameterOptions() const;
	
	TArray<FName> GetMaterialParameterOptions(UStaticMeshComponent* InputComponentParameter) const;

	void SetMeshMaterial(UStaticMeshComponent* InputMeshComponent, const FName& MeshMaterialSlotName, 
		const FName& MaterialParameterName, const FLinearColor& Color, 
		UMaterialInstanceDynamic* DynamicMaterialInstance);

};
