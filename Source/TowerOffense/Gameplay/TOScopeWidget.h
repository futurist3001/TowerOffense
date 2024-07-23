#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TOScopeWidget.generated.h"

class UOverlay;
class UImage;

UCLASS()
class TOWEROFFENSE_API UTOScopeWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UOverlay> ImageOverlay;

	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UImage> Image;
};
