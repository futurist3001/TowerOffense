#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TeamMemberInterface.h"
#include "TOGameModeBase.h"
#include "TOHealthComponent.h"

#include "TurretPawn.generated.h"

class AProjectile;
class UCapsuleComponent;
class UParticleSystem;
struct FInputActionValue;

UCLASS()
class TOWEROFFENSE_API ATurretPawn : public APawn, public ITeamMemberInterface
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	TObjectPtr<UTOHealthComponent> HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	TObjectPtr<UParticleSystem> DeathEfect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	TObjectPtr<UParticleSystem> FireEfect;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Team")
	ETeam Team;

	UPROPERTY(EditAnywhere, Category = "Turret")
	float TurretRotationSpeed;

	UPROPERTY(Transient)
	UMaterialInstanceDynamic* BaseDynamicMaterialInstance;

	UPROPERTY(Transient)
	UMaterialInstanceDynamic* TurretDynamicMaterialInstance;

	FRotator TargetAngle; // For rotation
	float RotationCurrentTime;
	FVector Start; // For fire start point
	FVector End; // For fire end point

public:
	ATurretPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	FORCEINLINE ETeam GetTeam_Implementation() const
	{
		return Team;
	}

	UFUNCTION()
	void HealthCheckedDeath(AActor* HealthKeeper, UTOHealthComponent* ParameterHealthComponent);

	UFUNCTION()
	void PrintCurrentHealth(AActor* HealthKeeper, UTOHealthComponent* ParameterHealthComponent);

protected:
	virtual void BeginPlay() override;
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
