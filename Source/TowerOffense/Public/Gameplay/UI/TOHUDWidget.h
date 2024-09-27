#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TOHUDWidget.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class TOWEROFFENSE_API UTOHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> EnergyBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> EnemiesTowersText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> AlliesTanksText;

public:
	void SetHealth(float CurrentHealth, float MaxHealth);
	void SetEnergy(float CurrentEnergy, float MaxEnergy);

	UFUNCTION()
	void SetEnemiesText(int32 TowersRemain);

	UFUNCTION()
	void SetAlliesText(int32 TanksRemain);

protected:
	virtual void NativeConstruct() override;
};
