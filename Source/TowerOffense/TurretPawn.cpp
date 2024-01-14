#include "TurretPawn.h"
#include "Components/CapsuleComponent.h"

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
	TurretMesh->SetupAttachment(RootComponent);
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
}


TArray<FName> ATurretPawn::GetBaseMeshMaterialSlotOptions() const
{
	return GetMaterialSlotOptions(BaseMesh);
}

TArray<FName> ATurretPawn::GetTurretMeshMaterialSlotOptions() const
{
	return GetMaterialSlotOptions(TurretMesh);
}

TArray<FName> ATurretPawn::GetMaterialSlotOptions(UStaticMeshComponent* InputComponentSlot) const
{
	TArray<FName> OptionSlotNames;

	UStaticMesh* StaticMeshComponent = InputComponentSlot->GetStaticMesh();

	if (StaticMeshComponent)
	{
		const auto& Materials = StaticMeshComponent->GetStaticMaterials();
		for (const FStaticMaterial& Material : Materials)
		{
			OptionSlotNames.Add(Material.MaterialSlotName);
		}
	}

	return OptionSlotNames;
}

TArray<FName> ATurretPawn::GetBaseMeshMaterialParameterOptions() const
{
	return GetMaterialParameterOptions(BaseMesh);
}

TArray<FName> ATurretPawn::GetTurretMeshMaterialParameterOptions() const
{
	return GetMaterialParameterOptions(TurretMesh);
}

TArray<FName> ATurretPawn::GetMaterialParameterOptions(UStaticMeshComponent* InputComponentParameter) const
{
	TArray<FName> OptionParameterNames;
	
	TArray<FMaterialParameterInfo> MaterialParameterInfo;
	TArray<FGuid> Guid;

	UStaticMesh* StaticMeshComponent = InputComponentParameter->GetStaticMesh();

	if (StaticMeshComponent)
	{
		int32 MaterialIndex = StaticMeshComponent->GetMaterialIndex(BaseMeshMaterialSlotName);

		if (MaterialIndex < 0)
		{
			MaterialIndex = 0;
		}

		UMaterialInterface* Material = StaticMeshComponent->GetMaterial(MaterialIndex);

		Material->GetAllVectorParameterInfo(MaterialParameterInfo, Guid);

		for (const FMaterialParameterInfo& Parameter : MaterialParameterInfo)
		{
			OptionParameterNames.Add(Parameter.Name);
		}
	}

	return OptionParameterNames;
}

void ATurretPawn::SetMeshMaterial(UStaticMeshComponent* InputMeshComponent, FName& MeshMaterialSlotName,
	FName& MaterialParameterName, FLinearColor& Color,
	UMaterialInstanceDynamic* DynamicMaterialInstance)
{
	int32 MaterialIndex = InputMeshComponent->GetMaterialIndex(MeshMaterialSlotName);
	UMaterialInterface* Material = InputMeshComponent->GetMaterial(MaterialIndex);

	DynamicMaterialInstance = UMaterialInstanceDynamic::Create(Material, this);
	DynamicMaterialInstance->SetVectorParameterValue(MaterialParameterName, Color);
	InputMeshComponent->SetMaterial(MaterialIndex, DynamicMaterialInstance);
}

void ATurretPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SetMeshMaterial(BaseMesh, BaseMeshMaterialSlotName,
		BaseMaterialParameterName, BaseColor, BaseDynamicMaterialInstance);

	SetMeshMaterial(TurretMesh, TurretMeshMaterialSlotName,
		TurretMaterialParameterName, TurretColor, TurretDynamicMaterialInstance);
}

/*void ATurretPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetMeshMaterial(BaseMesh, BaseMeshMaterialSlotName,
		BaseMaterialParameterName, BaseColor, BaseDynamicMaterialInstance);

	SetMeshMaterial(TurretMesh, TurretMeshMaterialSlotName,
		TurretMaterialParameterName, TurretColor, TurretDynamicMaterialInstance);
}*/
