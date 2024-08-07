#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TOHUDWidget.generated.h"

class UProgressBar;

UCLASS()
class TOWEROFFENSE_API UTOHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> EnergyBar;

public:
	void SetHealth(float CurrentHealth, float MaxHealth);
	void SetEnergy(float CurrentEnergy, float MaxEnergy);
};
