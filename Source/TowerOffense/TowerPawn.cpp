#include "TowerPawn.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

ATowerPawn::ATowerPawn(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));

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

	if (bOverlapped)
	{
		RotateTurret();

		UKismetSystemLibrary::PrintString(
			this, FString::Printf(TEXT("Pitch: %f, Yaw: %f, Roll: %f"), TargetAngle.Pitch, TargetAngle.Yaw, TargetAngle.Roll),
			true, false, FColor::Black, DeltaTime);
	}


	UKismetSystemLibrary::PrintString(
		this, FString::Printf(TEXT("X: %f, Y: %f, Z: %f"), 
			OverllapedActor->GetActorLocation().X, OverllapedActor->GetActorLocation().Y, OverllapedActor->GetActorLocation().Z),
		true, false, FColor::Turquoise, DeltaTime);

}

void ATowerPawn::RotateTurret()
{
	Super::RotateTurret();

	FRotator NewRotator = UKismetMathLibrary::FindLookAtRotation(
		this->GetActorLocation(), OverllapedActor->GetActorLocation());

	TargetAngle = FRotator(0.f, NewRotator.Yaw, 0.f);
}

void ATowerPawn::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		UKismetSystemLibrary::PrintString(this, "Overlap", true, false, FColor::Black, 5.f);

		bOverlapped = true;
		OverllapedActor = OtherActor;
}

void ATowerPawn::OnEndOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	bOverlapped = false;

}
