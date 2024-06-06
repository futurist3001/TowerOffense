#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

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
	TObjectPtr<UTextBlock> EndGameState;

	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UButton> RestartButton;

	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UButton> QuitButton;

public:
	UTOWinLoseWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;
};
