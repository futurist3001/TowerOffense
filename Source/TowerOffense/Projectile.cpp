#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AProjectile::AProjectile(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMovementComponent =
		CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	SetRootComponent(SphereComponent);
	ProjectileMesh->SetupAttachment(RootComponent);

	ProjectileMovementComponent->InitialSpeed = 1000.f;
	ProjectileMovementComponent->MaxSpeed = 3000.f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
	//UKismetSystemLibrary::PrintString(this, GetRootComponent()->GetName(), true, false, FColor::White, 2.f);
}

/*void AProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}*/

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
