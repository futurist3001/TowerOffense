#include "TankPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

ATankPawn::ATankPawn(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);

	bIsStopMoving = false;
	DoOnce = false;
}

void ATankPawn::MoveTriggeredValue(const FInputActionValue& Value)
{
	UKismetSystemLibrary::PrintString(this, "MoveTriggered", true, false, FColor::Blue, 5.f);

	MovementVector = Value.Get<FVector>();

	if (!DoOnce)
	{
		if (MovementVector == PreviousMovementVector)
		{
			SpeedStopBraking *= -1;
		}

		DoOnce = true;
	}
}

void ATankPawn::MoveTriggeredInstance(const FInputActionInstance& Instance)
{
	bIsStopMoving = false;

	CurrentTime = Instance.GetElapsedTime();
	CurrentSpeed = FMath::Lerp(SpeedStopBraking, Speed, FMath::Clamp(CurrentTime / AccelerationDuration, 0.f, 1.f));
	AddActorLocalOffset(MovementVector * CurrentSpeed, true, nullptr);

	SpeedStopGas = CurrentSpeed;
}

void ATankPawn::MoveCompleted()
{
	bIsStopMoving = true;
	CurrentTime = 0;
	DoOnce = false;

	PreviousMovementVector = MovementVector;
}

void ATankPawn::Turn(const FInputActionValue& Value)
{
	UKismetSystemLibrary::PrintString(this, "Turn", true, false, FColor::Green, 5.f);

	const float Rotator = Value.Get<float>();
	AddActorLocalRotation(FRotator(0.f, Rotator, 0.f), true, nullptr);
	TurretMesh->AddLocalRotation(FRotator(0.f, -Rotator, 0.f), false, nullptr);
}

void ATankPawn::Fire()
{
	Super::Fire();


}

void ATankPawn::RotateTurret()
{
	Super::RotateTurret();

	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHitResultUnderCursorByChannel(
		ETraceTypeQuery::TraceTypeQuery1, false, HitResult))
	{
		FRotator NewRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HitResult.ImpactPoint);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetControlRotation(
			FMath::RInterpTo(GetControlRotation(), FRotator(0.f, NewRotator.Yaw, 0.f), RotationCurrentTime, SpeedTurretRotation));

		TargetAngle = FRotator(0.f, NewRotator.Yaw + 180.f, 0.f);
	}
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(TankMappingContext, 0);
		}
	}
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsStopMoving)
	{
		CurrentTime += DeltaTime;
		CurrentSpeed = FMath::Lerp(SpeedStopGas, 0, FMath::Clamp(CurrentTime / AccelerationDuration, 0.f, 1.f));
		AddActorLocalOffset(MovementVector * CurrentSpeed, true, nullptr);


		SpeedStopBraking = -CurrentSpeed;
	}

	RotateTurret();

	DrawDebugSphere(GetWorld(), HitResult.Location, 20, 5, FColor(181, 0, 0), false, 0.5f, 0, 0.5);

	UKismetSystemLibrary::PrintString(
		this, FString::Printf(TEXT("X: %f, Y: %f, Z: %f"), HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, HitResult.ImpactPoint.Z),
		true, false, FColor::Blue, DeltaTime);
}

void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ATankPawn::MoveTriggeredValue);
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ATankPawn::MoveTriggeredInstance);
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Completed, this, &ATankPawn::MoveCompleted);

		EnhancedInputComponent->BindAction(TurnRightAction, ETriggerEvent::Triggered, this, &ATankPawn::Turn);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ATankPawn::Fire);
	}
}
