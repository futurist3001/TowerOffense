#include "TurretPawn.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ATurretPawn::ATurretPawn(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Component"));

	SetRootComponent(CapsuleComponent);

	BaseMesh->SetupAttachment(RootComponent);
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	TurretRotationSpeed = 1.f;
}

TArray<FName> ATurretPawn::GetBaseMeshMaterialSlotOptions() const
{
	return GetMaterialSlotOptions(BaseMesh);
}

TArray<FName> ATurretPawn::GetTurretMeshMaterialSlotOptions() const
{
	return GetMaterialSlotOptions(TurretMesh);
}

TArray<FName> ATurretPawn::GetMaterialSlotOptions(const UStaticMeshComponent* InputComponentSlot)
{
	TArray<FName> OptionSlotNames;

	if (const UStaticMesh* StaticMeshComponent = InputComponentSlot->GetStaticMesh())
	{
		for (const FStaticMaterial& Material : StaticMeshComponent->GetStaticMaterials())
		{
			OptionSlotNames.Add(Material.MaterialSlotName);
		}
	}

	return OptionSlotNames;
}

TArray<FName> ATurretPawn::GetBaseMeshMaterialParameterOptions() const
{
	return GetMaterialParameterOptions(BaseMesh, BaseMeshMaterialSlotName);
}

TArray<FName> ATurretPawn::GetTurretMeshMaterialParameterOptions() const
{
	return GetMaterialParameterOptions(TurretMesh, TurretMeshMaterialSlotName);
}

TArray<FName> ATurretPawn::GetMaterialParameterOptions(
	const UStaticMeshComponent* InputComponentParameter, FName MeshMaterialSlotName)
{
	TArray<FName> OptionParameterNames;

	if (const UStaticMesh* StaticMeshComponent = InputComponentParameter->GetStaticMesh())
	{
		int32 MaterialIndex = StaticMeshComponent->GetMaterialIndex(MeshMaterialSlotName);
		MaterialIndex = FMath::Max(MaterialIndex, 0);

		const UMaterialInterface* Material = StaticMeshComponent->GetMaterial(MaterialIndex);
		TArray<FMaterialParameterInfo> MaterialParameterInfo;
		TArray<FGuid> Guid;

		Material->GetAllVectorParameterInfo(MaterialParameterInfo, Guid);

		for (const FMaterialParameterInfo& Parameter : MaterialParameterInfo)
		{
			OptionParameterNames.Add(Parameter.Name);
		}
	}

	return OptionParameterNames;
}

void ATurretPawn::SetMeshMaterial(
	UStaticMeshComponent* MeshComponent, FName MeshMaterialSlotName, FName MaterialParameterName,
	const FLinearColor& Color, UMaterialInstanceDynamic*& DynamicMaterialInstance)
{
	if (IsValid(MeshComponent))
	{
		const int32 MaterialIndex = MeshComponent->GetMaterialIndex(MeshMaterialSlotName);
		UMaterialInterface* Material = MeshComponent->GetMaterial(MaterialIndex);

		DynamicMaterialInstance = UMaterialInstanceDynamic::Create(Material, this);
		DynamicMaterialInstance->SetVectorParameterValue(MaterialParameterName, Color);
		MeshComponent->SetMaterial(MaterialIndex, DynamicMaterialInstance);
	}
}

void ATurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotationCurrentTime = DeltaTime;
}

// using OnConstruction() leads to unpredictable results
void ATurretPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SetMeshMaterial(BaseMesh, BaseMeshMaterialSlotName,
		BaseMaterialParameterName, BaseColor, BaseDynamicMaterialInstance);

	SetMeshMaterial(TurretMesh, TurretMeshMaterialSlotName,
		TurretMaterialParameterName, TurretColor, TurretDynamicMaterialInstance);
}

void ATurretPawn::RotateTurret()
{
	TurretMesh->SetRelativeRotation(
		FMath::RInterpTo(TurretMesh->GetRelativeRotation(), TargetAngle, RotationCurrentTime, TurretRotationSpeed));
}

void ATurretPawn::Fire()
{
	UKismetSystemLibrary::PrintString(this, "Fire", true, false, FColor::Red, 2.f);
}