// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseButtonWidget.generated.h"

class UPauseMenuWidget;
/**
* 
*/
UCLASS()
class RADIANCE_API UPauseButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY ( meta = ( BindWidget ) )
		class UButton* PauseButton;

	virtual void NativeConstruct() override;

	UPROPERTY( EditDefaultsOnly,BlueprintReadWrite )
		TSubclassOf<UPauseMenuWidget>			m_pcPauseWidget;

public:

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ~UMain_MenuWidget()
	// Author			: Michalis Stratis
	// Purpose			: UMain_MenuWidget destructor
	//-----------------------------------------------------------------------------------------------------------------------------
	~UPauseButtonWidget ( );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: StartGameButtonClicked()
	// Author			: Michalis Stratis
	// Purpose			: The functionality of the play button when clicked 
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void PauseButtonClicked();

private:
		UPauseMenuWidget* PauseWidget;
};// Fill out your copyright notice in the Description page of Project Settings.

