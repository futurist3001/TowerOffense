#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"

AProjectile::AProjectile(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	//RootComponent = ProjectileMesh;

	ProjectileMovementComponent =
		CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	ProjectileMovementComponent->InitialSpeed = 1000.f;
	ProjectileMovementComponent->MaxSpeed = 3000.f;
}
