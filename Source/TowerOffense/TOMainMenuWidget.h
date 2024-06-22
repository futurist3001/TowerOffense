#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TOMainMenuWidget.generated.h"

class UButton;
class UOverlay;
class UTextBlock;


UCLASS()
class TOWEROFFENSE_API UTOMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextStartGame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextQuitGame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> OverlayGameNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> GameNameText;

protected:
	virtual void NativeConstruct() override;
};
