#include "TOPreparationWidget.h"

#include "Components/TextBlock.h"
#include "TowerOffense/Gameplay/ModeControl/TOGameModeBase.h"

void UTOPreparationWidget::SetPreparationText()
{
	ATOGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ATOGameModeBase>();
	TextPreparation->SetText(GameMode->GetPreparationText());
}
