#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "TOHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWEROFFENSE_API UTOHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTOHealthComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float DefaultHealth;

	UPROPERTY(BlueprintReadOnly)
	float Health;

	UFUNCTION()
	void TakeDamage(
		AActor* DamagedActor, float Damage, const UDamageType* DamageType,
		AController* InstigatedBy, AActor* DamageCauser);
};
