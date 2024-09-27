#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "HealthTurretWidget.generated.h"

class UProgressBar;

UCLASS()
class TOWEROFFENSE_API UHealthTurretWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

public:
	void SetHealthBar(float CurrentHealth, float MaxHealth);
};
