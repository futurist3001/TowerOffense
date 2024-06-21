#include "TowerPawn.h"

#include "TankPawn.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectile.h"

ATowerPawn::ATowerPawn(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ShootingZone"));
	SphereComponent->SetupAttachment(RootComponent);
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
	}

	DrawDebugLine(
		GetWorld(), ProjectileSpawnPoint->GetComponentLocation(),
		ProjectileSpawnPoint->GetComponentLocation() + ProjectileSpawnPoint->GetForwardVector() * 100.f,
		FColor::Black, false, 1.f);
}

void ATowerPawn::RotateTurret()
{
	if (!IsTheSameTeam(OverlapedActor[0]))
	{
		Super::RotateTurret();

		const FRotator NewRotator = UKismetMathLibrary::FindLookAtRotation(
			GetActorLocation(), OverlapedActor[0]->GetActorLocation());

		TargetAngle = FRotator(0.f, NewRotator.Yaw - 90.f, 0.f);
	}
}

void ATowerPawn::Fire()
{
	if (IsLookToTank() && !IsTheSameTeam(OverlapedActor[0]))
	{
		Start = ProjectileSpawnPoint->GetComponentLocation();
		End = OverlapedActor[0]->GetActorLocation();

		Super::Fire();
	}
}

bool ATowerPawn::IsLookToTank()
{
	FHitResult HitResult;

	FVector StartPointLook = ProjectileSpawnPoint->GetComponentLocation();
	FVector EndPointLook = StartPointLook + ProjectileSpawnPoint->GetForwardVector() * 5000.f;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartPointLook, EndPointLook, ECollisionChannel::ECC_Visibility))
	{
		if (HitResult.GetActor()->IsA<ATankPawn>())
		{
			return true;
		}
	}

	return false;
}

bool ATowerPawn::IsTheSameTeam(AActor* Actor)
{
	if (Actor->IsA<ATurretPawn>())
	{
		const ATurretPawn* TurretPawn = Cast<ATurretPawn>(Actor);

		if (this->GetTeam() == TurretPawn->GetTeam())
		{
			return true;
		}
	}

	return false;
}

void ATowerPawn::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	if (!IsTheSameTeam(OtherActor))
	{
		if (OtherActor && OtherActor->IsA<ATankPawn>())
		{
			UKismetSystemLibrary::PrintString(this, "Overlap", true, false, FColor::Black, 5.f);

			OverlapedActor.Add(OtherActor);

			GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATowerPawn::Fire, 2.f, true);
		}
	}
}

void ATowerPawn::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (!IsTheSameTeam(OtherActor))
	{
		if (OtherActor && OtherActor->IsA<ATankPawn>())
		{
			UKismetSystemLibrary::PrintString(this, "EndOverlap", true, false, FColor::Purple, 5.f);

			OverlapedActor.RemoveSingleSwap(OtherActor); // if the actor leave shooting zone, overlapped actor must be deleted from array

			if (OverlapedActor.IsEmpty())
			{
				GetWorldTimerManager().ClearTimer(FireTimerHandle);
			}
		}
	}
}
