#include "TOPreparationWidget.h"

#include "Components/TextBlock.h"
#include "TOGameModeBase.h"

void UTOPreparationWidget::SetPreparationText()
{
	auto* GameMode = GetWorld()->GetAuthGameMode<ATOGameModeBase>();
	TextPreparation->SetText(GameMode->GetPreparationText());
}
