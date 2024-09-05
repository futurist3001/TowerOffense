#include "TankPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Landscape.h"
#include "NiagaraFunctionLibrary.h"
#include "Projectile.h"
#include "TOCameraShake.h"
#include "TOPlayerController.h"

ATankPawn::ATankPawn(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));

	RightTankTrack = CreateDefaultSubobject<USceneComponent>(TEXT("Right Tank Track"));
	LeftTankTrack = CreateDefaultSubobject<USceneComponent>(TEXT("Left Tank Track"));
	RightTankTrackRotation = CreateDefaultSubobject<USceneComponent>(TEXT("Right Tank Track Rotation"));
	LeftTankTrackRotation = CreateDefaultSubobject<USceneComponent>(TEXT("Left Tank Track Rotation"));

	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);

	RightTankTrack->SetupAttachment(BaseMesh);
	LeftTankTrack->SetupAttachment(BaseMesh);
	RightTankTrackRotation->SetupAttachment(BaseMesh);
	LeftTankTrackRotation->SetupAttachment(BaseMesh);

	CurrentTime = 0.f;
	CurrentSpeed = 0.f;
	SpeedStopGas = 0.f;
	SpeedStopBraking = 0.f;
	YawTurnRotator = 0.f;
	MaxEnergy = 50.f;
	CurrentEnergy = MaxEnergy;
	OldShootTime = 10.f;
	MaxFireHorizontalAngle = 15.f;

	bIsStopMoving = false;
	bReverseAttempt = false;
	bPlayedTurretRotationSoundIteration = false;
	bIsOldShoot = false;
	bIsCollision = false;

	MovementEffect = nullptr;
}

void ATankPawn::MoveStarted()
{
	if (MovementSound)
	{
		MovementAudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), MovementSound);
		MovementAudioComponent->Play();
	}
}

void ATankPawn::MoveTriggeredValue(const FInputActionValue& Value)
{
	MovementVector = Value.Get<FVector>();

	if (!bReverseAttempt) // this will release once
	{
		if (MovementVector == PreviousMovementVector)
		{
			SpeedStopBraking *= -1;
		}
		bReverseAttempt = true;
	}

	if (MovementEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(), MovementEffect, RightTankTrack->GetComponentLocation());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(), MovementEffect, LeftTankTrack->GetComponentLocation());
	}
}

void ATankPawn::MoveTriggeredInstance(const FInputActionInstance& Instance)
{
	bIsStopMoving = false;

	if (!bIsCollision)
	{
		CurrentTime = Instance.GetElapsedTime();
		CurrentSpeed = FMath::Lerp(SpeedStopBraking, Speed, FMath::Clamp(CurrentTime / AccelerationDuration, 0.f, 1.f));
		AddActorLocalOffset(MovementVector * CurrentSpeed, true, nullptr);

		SpeedStopGas = CurrentSpeed;
	}
}

void ATankPawn::MoveCompleted()
{
	bIsStopMoving = true;
	CurrentTime = 0;
	bReverseAttempt = false;

	PreviousMovementVector = MovementVector;

	if (MovementSound && MovementAudioComponent && MovementAudioComponent->IsValidLowLevel())
	{
		MovementAudioComponent->Stop();
		MovementAudioComponent->DestroyComponent();
	}
}

void ATankPawn::StopCollision()
{
	bIsCollision = false;
}

void ATankPawn::Turn(const FInputActionValue& Value)
{
	YawTurnRotator = Value.Get<float>();
	AddActorLocalRotation(FRotator(0.f, YawTurnRotator, 0.f), true, nullptr);

	TurretMesh->AddLocalRotation(FRotator(0.f, -YawTurnRotator, 0.f), false, nullptr);
	TargetAngle.Yaw -= YawTurnRotator;

	if (MovementEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(), MovementEffect, RightTankTrackRotation->GetComponentLocation());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(), MovementEffect, LeftTankTrackRotation->GetComponentLocation());
	}
}

void ATankPawn::Fire()
{
	if (CurrentTimeFire >= FireInterval && CurrentEnergy > 0.f)
	{
		Start = ProjectileSpawnPoint->GetComponentLocation();
		End = Start + (FRotator(
			TurretMesh->GetComponentRotation().Pitch + PitchAimingRotator, TurretMesh->GetComponentRotation().Yaw + 90.f,
			TurretMesh->GetComponentRotation().Roll)).GetNormalized().Vector() * 1000.f;

		Super::Fire();

		if (TOCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayWorldCameraShake(
				GetWorld(), TOCameraShakeClass, GetActorLocation(), 0.0f, 1000.0f, 1.f);
		}

		CurrentTimeFire = 0.0f;
		CurrentEnergy -= 10.f;

		bIsOldShoot = false;
	}
}

void ATankPawn::NotifyHit(
	UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(
		MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (Other && !Other->IsA<AProjectile>() && !Other->IsA<ALandscape>())
	{
		MoveCompleted();

		bIsCollision = true;
		CurrentSpeed = 0.0f;
		SpeedStopBraking = 0.0f;
		SpeedStopGas = 0.0f;

		MovementVector = FVector::ZeroVector;

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle, this, &ATankPawn::StopCollision, 0.5f, false);
	}
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

void ATankPawn::Aiming(const FInputActionValue& Value)
{
	float AimingValue = Value.Get<float>();
	PitchAimingRotator += AimingValue;

	if (PitchAimingRotator > MaxFireHorizontalAngle) // for limiting range of horizontal aiming
	{
		PitchAimingRotator = MaxFireHorizontalAngle;
	}
	else if (PitchAimingRotator < 0.f) // for limiting range of horizontal aiming
	{
		PitchAimingRotator = 0.f;
	}
}

void ATankPawn::AdjustTurretPosition() // Attach camera to the current turret direction (must use this func manually diring the game)
{
	YawCameraRotator =
		TurretMesh->GetComponentRotation().Yaw + 90.f;

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetControlRotation(FRotator(0.f, YawCameraRotator, 0.f));
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
	BaseMesh->SetWorldRotation(GetActorRotation() - FRotator(0.f, 90.f, 0.f));
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

	if (!bPlayedTurretRotationSoundIteration && bIsRotate)
	{
		// Play Sound

		if (TurretRotationSound)
		{
			TurretRotationAudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), TurretRotationSound);
			TurretRotationAudioComponent->Play();

			bPlayedTurretRotationSoundIteration = true;
		}
	}

	else if (bPlayedTurretRotationSoundIteration && !bIsRotate)
	{
		// Stop and delete sound

		if (TurretRotationSound && TurretRotationAudioComponent)
		{
			TurretRotationAudioComponent->Stop();
			TurretRotationAudioComponent->DestroyComponent();

			bPlayedTurretRotationSoundIteration = false;
		}
	}

	GetWorld()->LineTraceSingleByChannel(
		ShootingPoint, TurretMesh->GetComponentLocation(), 
		TurretMesh->GetComponentLocation() + UKismetMathLibrary::GetForwardVector(
			TurretMesh->GetComponentRotation() + FRotator(PitchAimingRotator, 90.f, 0.f)) * 100000.f,
		ECollisionChannel::ECC_Camera);

	if (ShootingPoint.Location != FVector(0.f,0.f,0.f))
	{
		DrawDebugSphere(
			GetWorld(), FVector(ShootingPoint.Location.X, ShootingPoint.Location.Y, ShootingPoint.Location.Z + 150.f),
			35, 15, FColor::Red, false, 0.03f, 0, 0.5);
	}

	CurrentTimeFire += DeltaTime;

	if (CurrentTimeFire > OldShootTime)
	{
		bIsOldShoot = true;
	}

	if (CurrentEnergy < MaxEnergy)
	{
		RechargeTimeProjectile += DeltaTime;
	}

	if (RechargeTimeProjectile >= RechargeInterval && CurrentEnergy < MaxEnergy)
	{
		CurrentEnergy += 10.f;
		RechargeTimeProjectile = 0.0f;
	}
}

void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Started, this, &ATankPawn::MoveStarted);
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ATankPawn::MoveTriggeredValue);
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ATankPawn::MoveTriggeredInstance);
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Completed, this, &ATankPawn::MoveCompleted);

		EnhancedInputComponent->BindAction(TurnRightAction, ETriggerEvent::Triggered, this, &ATankPawn::Turn);
		EnhancedInputComponent->BindAction(RotateTurretAction, ETriggerEvent::Triggered, this, &ATankPawn::Rotate);
		EnhancedInputComponent->BindAction(AimingAction, ETriggerEvent::Triggered, this, &ATankPawn::Aiming);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ATankPawn::Fire);
	}
}
