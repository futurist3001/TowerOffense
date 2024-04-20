#include "TOHealthComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "TurretPawn.h"

UTOHealthComponent::UTOHealthComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;

	DefaultHealth = 100.f;
	Health = DefaultHealth;
}

void UTOHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if (IsValid(Owner))
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UTOHealthComponent::TakeDamage);
		HealthChanged.AddDynamic(this, &UTOHealthComponent::HealthChange);
	}
}

void UTOHealthComponent::TakeDamage(
	AActor* DamagedActor, float Damage, const UDamageType* DamageType, 
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);
	
	HealthChanged.Broadcast(GetOwner(), this);
}

void  UTOHealthComponent::HealthChange(AActor* HealthKeeper, UTOHealthComponent* ParameterHealthComponent)
{
	if (HealthKeeper && HealthKeeper->IsA<ATurretPawn>())
	{
		UKismetSystemLibrary::PrintString(
			GetOwner(), FString::Printf(TEXT("Health: %f"), ParameterHealthComponent->Health),
			true, false, FColor::Green, 3.f);
	}
}