#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Projectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class TOWEROFFENSE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	TObjectPtr<UParticleSystem> DamageEffect;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Damage;

public:	
	AProjectile(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	FORCEINLINE float GetDamage() const
	{
		return Damage;
	}

	void FireInDirection(const FVector& ShootDirection);

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);
};
