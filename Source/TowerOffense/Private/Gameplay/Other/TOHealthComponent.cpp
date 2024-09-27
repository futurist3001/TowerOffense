#include "TowerOffense/Public/Gameplay/Other/TOHealthComponent.h"

UTOHealthComponent::UTOHealthComponent(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;

	DefaultHealth = 100.0f;
}

void UTOHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;

	AActor* Owner = GetOwner();

	if (IsValid(Owner))
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UTOHealthComponent::TakeDamage);
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