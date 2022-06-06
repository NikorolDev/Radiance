// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget_Base.generated.h"

/**
 * 
 */

UCLASS()
class RADIANCE_API UMenuWidget_Base : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY ( meta = ( BindWidget ) )
		class UButton* QuitGame;

	UPROPERTY ( meta = ( BindWidget ) )
		class UImage* Background;

	UPROPERTY( Category = Audio, EditDefaultsOnly, meta = ( DisplayName = "Main Button Clicked" ) )
		USoundBase*							m_pcButtonClickedSound;

	UPROPERTY( Category = Audio, EditDefaultsOnly, meta = ( DisplayName = "Main Button Hovered" ) )
		USoundBase*							m_pcButtonHoveredSound;

	UPROPERTY( Category = Audio, EditDefaultsOnly, meta = ( DisplayName = "Options Button Clicked" ) )
		USoundBase*							m_pcOptionsButtonClickedSound;

	UPROPERTY( Category = Audio, EditDefaultsOnly, meta = ( DisplayName = "Pause UI Sound Clicked" ) )
		USoundBase*							m_pcPauseClickedSound;

	UPROPERTY( Category = Audio, EditDefaultsOnly, meta = ( DisplayName = "Pause UI Sound Hovered" ) )
		USoundBase*							m_pcPauseHoveredSound;

	// Fade Animation. (Michalis Stratis)
	UPROPERTY ( Transient, meta = ( BindWidgetAnim ) )
		UWidgetAnimation* FadeOut;

	// Fade Animation. (Michalis Stratis)
	UPROPERTY ( Transient, meta = ( BindWidgetAnim ) )
		UWidgetAnimation* FadeIn;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: NativeConstruct()
	// Author			: Michalis Stratis
	// Purpose			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void NativeConstruct() override;

private:

	APlayerController* PC;

public:

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ~UMain_MenuWidget()
	// Author			: Michalis Stratis
	// Purpose			: UMain_MenuWidget destructor
	//-----------------------------------------------------------------------------------------------------------------------------
	~UMenuWidget_Base ( );

	FTimerHandle TimerHandle;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: QuitGameButtonClicked()
	// Author			: Michalis Stratis
	// Purpose			: The functionality of the quit button when clicked 
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void QuitGameButtonClicked( );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: QuitGameButtonClicked()
	// Author			: Michalis Stratis
	// Purpose			: The functionality of the quit button when clicked 
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void QuitGameButtonHovered( );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ShowMenu()
	// Author			: Michalis Stratis
	// Purpose			: This function shows the menu 
	//-----------------------------------------------------------------------------------------------------------------------------
	void ShowMenu ( );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: HideMenu()
	// Author			: Michalis Stratis
	// Purpose			: This function hides the menu 
	//-----------------------------------------------------------------------------------------------------------------------------
	void HideMenu ( );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GoToMap()
	// Author			: Michalis Stratis
	// Purpose			: This function transitions to a specific map/level
	//-----------------------------------------------------------------------------------------------------------------------------
	void GoToMap ( FName level );

	void	ExitGame ( );
	
	void PlayUISound ( USoundBase* UIAudio );
};
