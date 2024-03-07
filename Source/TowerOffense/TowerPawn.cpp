#include "TowerPawn.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

ATowerPawn::ATowerPawn(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ShootingZone"));
	SphereComponent->SetupAttachment(RootComponent);

	DoOnce = true;
	TimeFire = 0.f;
}

void ATowerPawn::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);

	OverllapedActor.Empty();
}

void ATowerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!OverllapedActor.IsEmpty())
	{
		RotateTurret();

		UKismetSystemLibrary::PrintString(this, TargetAngle.ToString(), true, false, FColor::Black, DeltaTime);

		UKismetSystemLibrary::PrintString(
			this, OverllapedActor[0]->GetActorLocation().ToString(), true, false, FColor::Turquoise, DeltaTime);

		TimeFire += DeltaTime;

		if (TimeFire > 5.f)
		{
			Fire();
			TimeFire = 0.f;
		}
	}

	if (OverllapedActor.IsEmpty())
	{
		TimeFire = 0.f;
	}
}

void ATowerPawn::RotateTurret()
{
	Super::RotateTurret();

	FRotator NewRotator = UKismetMathLibrary::FindLookAtRotation(
		this->GetActorLocation(), OverllapedActor[0]->GetActorLocation());

	TargetAngle = FRotator(0.f, NewRotator.Yaw - 90, 0.f);
}

void ATowerPawn::Fire()
{
	Super::Fire();


}

void ATowerPawn::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UKismetSystemLibrary::PrintString(this, "Overlap", true, false, FColor::Black, 5.f);

	if (OtherActor && OtherActor->IsA<APawn>())
	{
		if (!DoOnce)
		{
			OverllapedActor.Add(OtherActor);
			DoOnce = true;
		}
	}
}

void ATowerPawn::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	DoOnce = false;

	// if the actor leave shooting zone, overlapped actor must be deleted from array
	OverllapedActor.RemoveSingle(OtherActor);
}
