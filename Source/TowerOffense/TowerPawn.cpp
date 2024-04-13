#include "TowerPawn.h"

#include "TankPawn.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

ATowerPawn::ATowerPawn(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ShootingZone"));
	SphereComponent->SetupAttachment(RootComponent);

	BaseMesh->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
	ProjectileSpawnPoint->SetRelativeLocation(FVector(0.f, 190.f, 250.f));

	TimeFire = 0.f;
}

void ATowerPawn::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);
}

void ATowerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!OverlapedActor.IsEmpty())
	{
		RotateTurret();

		UKismetSystemLibrary::PrintString(this, TargetAngle.ToString(), true, false, FColor::Black, DeltaTime);

		UKismetSystemLibrary::PrintString(
			this, OverlapedActor[0]->GetActorLocation().ToString(), true, false, FColor::Turquoise, DeltaTime);

		TimeFire += DeltaTime;

		if (TimeFire > 5.f)
		{
			Fire();
			TimeFire = 0.f;
		}
	}

	else if (OverlapedActor.IsEmpty())
	{
		TimeFire = 0.f;
	}
}

void ATowerPawn::RotateTurret()
{
	Super::RotateTurret();

	const FRotator NewRotator = UKismetMathLibrary::FindLookAtRotation(
		GetActorLocation(), OverlapedActor[0]->GetActorLocation());

	TargetAngle = FRotator(0.f, NewRotator.Yaw - 90, 0.f);
}

void ATowerPawn::Fire()
{
	Super::Fire();
}

void ATowerPawn::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	if (OtherActor && OtherActor->IsA<ATankPawn>())
	{
		UKismetSystemLibrary::PrintString(this, "Overlap", true, false, FColor::Black, 5.f);

		OverlapedActor.Add(OtherActor);
	}
}

void ATowerPawn::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA<ATankPawn>())
	{
		UKismetSystemLibrary::PrintString(this, "EndOverlap", true, false, FColor::Purple, 5.f);

		OverlapedActor.RemoveSingleSwap(OtherActor); // if the actor leave shooting zone, overlapped actor must be deleted from array
	}
}
