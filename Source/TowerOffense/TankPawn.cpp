#include "TankPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
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

	CurrentTime = 0.f;
	CurrentSpeed = 0.f;
	SpeedStopGas = 0.f;
	SpeedStopBraking = 0.f;
	YawTurnRotator = 0.f;

	bIsStopMoving = false;
	bReverseAttempt = false;
}

void ATankPawn::MoveTriggeredValue(const FInputActionValue& Value)
{
	MovementVector = Value.Get<FVector>();

	if (!bReverseAttempt)
	{
		if (MovementVector == PreviousMovementVector)
		{
			SpeedStopBraking *= -1;
		}
		bReverseAttempt = true;
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
	bReverseAttempt = false;

	PreviousMovementVector = MovementVector;
}

void ATankPawn::Turn(const FInputActionValue& Value)
{
	YawTurnRotator = Value.Get<float>();
	AddActorLocalRotation(FRotator(0.f, YawTurnRotator, 0.f), true, nullptr);

	TurretMesh->AddLocalRotation(FRotator(0.f, -YawTurnRotator, 0.f), false, nullptr);
	TargetAngle.Yaw -= YawTurnRotator;
}

void ATankPawn::Fire()
{
	Start = ProjectileSpawnPoint->GetComponentLocation();
	End = Start + (FRotator(
		TurretMesh->GetComponentRotation().Pitch, TurretMesh->GetComponentRotation().Yaw + 90.f,
		TurretMesh->GetComponentRotation().Roll)).GetNormalized().Vector() * 1000.f;

	Super::Fire();
}

void ATankPawn::RotateTurret()
{
	Super::RotateTurret();
}

void ATankPawn::Rotate(const FInputActionValue& Value)
{
	float RotateValue = Value.Get<float>();
	YawCameraRotator += RotateValue;
	TargetAngle.Yaw += RotateValue;

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetControlRotation(FRotator(0.f, YawCameraRotator, 0.f));
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	BaseMesh->SetRelativeRotation(GetActorRotation());
	YawCameraRotator = GetActorRotation().Yaw;

	if (const auto* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (auto* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				Subsystem->AddMappingContext(TankMappingContext, 0);
			}
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

	GetWorld()->LineTraceSingleByChannel(
		ShootingPoint, TurretMesh->GetComponentLocation(), 
		TurretMesh->GetComponentLocation() + UKismetMathLibrary::GetForwardVector(
			TurretMesh->GetComponentRotation() + FRotator(0.f, 90.f, 0.f)) * 100000.f,
		ECollisionChannel::ECC_Camera);

	if (ShootingPoint.Location != FVector(0.f,0.f,0.f))
	{
		DrawDebugSphere(
			GetWorld(), FVector(ShootingPoint.Location.X, ShootingPoint.Location.Y, ShootingPoint.Location.Z + 150.f),
			35, 15, FColor::Red, false, 0.03f, 0, 0.5);
	}
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
		EnhancedInputComponent->BindAction(RotateTurretAction, ETriggerEvent::Triggered, this, &ATankPawn::Rotate);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ATankPawn::Fire);
	}
}