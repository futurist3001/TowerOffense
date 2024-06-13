#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TOGameModeBase.h"

#include "TOWinLoseWidget.generated.h"

class UTextBlock;
class UButton;
class UOverlay;

UCLASS()
class TOWEROFFENSE_API UTOWinLoseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UOverlay> TextOverlay;

	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UTextBlock> EndGameStateText;

	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UButton> RestartButton;

	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UButton> QuitButton;

public:
	UTOWinLoseWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void SetEndGameStateTextColor(EEndGameState EndGameState);

protected:
	virtual void NativeConstruct() override;
};
