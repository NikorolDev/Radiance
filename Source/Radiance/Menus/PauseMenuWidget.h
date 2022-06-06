// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget_Base.h"
#include "PauseMenuWidget.generated.h"

class UMainMenuWidget;
class UOptionsMenuWidget;
class APlayerCharacter;
/**
 * 
 */
UCLASS()
class RADIANCE_API UPauseMenuWidget : public UMenuWidget_Base
{
	GENERATED_BODY()

protected:

	UPROPERTY ( meta = ( BindWidget ) )
		class UButton* ReturnToMainMenu;

	UPROPERTY ( meta = ( BindWidget ) )
		class UButton* ResumeButton;


	UPROPERTY ( meta = ( BindWidget ) )
		class UButton* Options;

	virtual void NativeConstruct() override;
	
	UPROPERTY( EditDefaultsOnly,BlueprintReadWrite )
		TSubclassOf<UMainMenuWidget>			m_pcMenuWidget;

	UPROPERTY( EditDefaultsOnly,BlueprintReadWrite )
		TSubclassOf<UOptionsMenuWidget>			m_pcOptionsWidget;

	APlayerCharacter* m_pcPlayer;

public:

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ~UMain_MenuWidget()
	// Author			: Michalis Stratis
	// Purpose			: UMain_MenuWidget destructor
	//-----------------------------------------------------------------------------------------------------------------------------
	~UPauseMenuWidget ( );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: MainMenuButtonClicked()
	// Author			: Michalis Stratis
	// Purpose			: The functionality of the main menu button when clicked 
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void MainMenuButtonClicked();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: MainMenuButtonHovered()
	// Author			: Michalis Stratis
	// Purpose			: The functionality of the play button when hovered 
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void MainMenuButtonHovered();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OptionsButtonClicked()
	// Author			: Michalis Stratis
	// Purpose			: The functionality of the options button when clicked 
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void OptionsButtonClicked();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OptionsButtonHovered()
	// Author			: Michalis Stratis
	// Purpose			: The functionality of the options button when hovered 
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void OptionsButtonHovered();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ResumeButtonClicked()
	// Author			: Michalis Stratis
	// Purpose			: The functionality of the resume button when clicked 
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION ( )
		void ResumeButtonClicked ( );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ResumeButtonHovered()
	// Author			: Michalis Stratis
	// Purpose			: The functionality of the resume button when hovered 
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION ( )
		void ResumeButtonHovered ( );

	void SetPlayerCharacter(APlayerCharacter* pcPlayer);

private:
	UMainMenuWidget* MenuWidget;

	UOptionsMenuWidget* OptionsWidget;
	
};
