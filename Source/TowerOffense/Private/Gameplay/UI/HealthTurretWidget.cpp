#include "TowerOffense/Public/Gameplay/UI/HealthTurretWidget.h"

#include "Components/ProgressBar.h"

void UHealthTurretWidget::SetHealthBar(float CurrentHealth, float MaxHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(CurrentHealth / MaxHealth);
	}
}
