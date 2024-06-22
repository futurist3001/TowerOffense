#include "TOMainMenuWidget.h"

#include "Components/Button.h"
#include "TOMMGameModeBase.h"

void UTOMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto* MMGameMode = GetWorld()->GetAuthGameMode<ATOMMGameModeBase>();

	StartGameButton->OnClicked.AddDynamic(MMGameMode, &ATOMMGameModeBase::StartGame);
	QuitGameButton->OnClicked.AddDynamic(MMGameMode, &ATOMMGameModeBase::QuitGame);
}
