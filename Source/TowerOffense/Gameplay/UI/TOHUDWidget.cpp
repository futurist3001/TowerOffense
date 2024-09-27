#include "TOHUDWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "TowerOffense/Gameplay/ModeControl/TOGameModeBase.h"

void UTOHUDWidget::SetHealth(float CurrentHealth, float MaxHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(CurrentHealth / MaxHealth);
	}
}

void UTOHUDWidget::SetEnergy(float CurrentEnergy, float MaxEnergy)
{
	if (EnergyBar)
	{
		EnergyBar->SetPercent(CurrentEnergy / MaxEnergy);
	}
}

void UTOHUDWidget::SetEnemiesText(int32 TowersRemain)
{
	if (EnemiesTowersText)
	{
		FString FormattedString = FString::Printf(TEXT("Towers remain: %d"), TowersRemain);

		EnemiesTowersText->SetText(FText::FromString(FormattedString));
	}
}

void UTOHUDWidget::SetAlliesText(int32 TanksRemain)
{
	if (AlliesTanksText)
	{
		FString FormattedString = FString::Printf(TEXT("Tanks remain: %d"), TanksRemain);

		AlliesTanksText->SetText(FText::FromString(FormattedString));
	}
}

void UTOHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (auto* GameMode = GetWorld()->GetAuthGameMode<ATOGameModeBase>())
	{
		GameMode->OnTowerDestroyed.AddDynamic(this, &UTOHUDWidget::SetEnemiesText);
		GameMode->OnTankDestroyed.AddDynamic(this, &UTOHUDWidget::SetAlliesText);

		SetEnemiesText(GameMode->GetNumberTowers());
		SetAlliesText(GameMode->GetNumberTanks());
	}
}
