#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AProjectile::AProjectile(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMovementComponent =
		CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	SetRootComponent(ProjectileMesh);

	ProjectileMovementComponent->InitialSpeed = 1000.f;
	ProjectileMovementComponent->MaxSpeed = 3000.f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	//UKismetSystemLibrary::PrintString(this, GetRootComponent()->GetName(), true, false, FColor::White, 2.f);
}

void AProjectile::OnHit(
	UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	//UKismetSystemLibrary::PrintString(this, "Hit", true, false, FColor::Red, 2.f);

	if (OtherActor && (OtherActor != GetOwner()) && (OtherActor != GetInstigator()))
	{
		this->Destroy();
	}
}
