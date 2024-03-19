#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOWEROFFENSE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

public:	
	AProjectile(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
