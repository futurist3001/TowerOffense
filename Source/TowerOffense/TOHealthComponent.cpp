#include "TOHealthComponent.h"

UTOHealthComponent::UTOHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	DefaultHealth = 100.f;
	Health = DefaultHealth;
}

void UTOHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if (Owner)
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
}


