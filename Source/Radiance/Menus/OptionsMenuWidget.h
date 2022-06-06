// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsMenuWidget.generated.h"

// Forward class declarations
class UButton;
class USlider;
class USoundMix;
class UTextBlock;

class URadianceGameInstance;
class URadianceSaveGame;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UOptionsMenuWidget
// Author				: Nikodem Hamrol
// Classes Inherited	: UUserWidget
// Purpose				: This class is responsible for settings the avaliable options, such as volume and toggle subtitles.
//----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API UOptionsMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetPreviousAccessedWidget( UUserWidget* pcPreviousAccessedWidget )
	// Author			: Nikodem Hamrol
	// Purpose			: To set the previous accessed widget so that it can correctly go back to that previous widget.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetPreviousAccessedWidget( UUserWidget* pcPreviousAccessedWidget );

protected:
	// The button that will apply settings, which saves it to the save game file.
	UPROPERTY( meta = ( BindWidget ) )
		UButton* ApplySettingsButton;

	// The button that will go back to the previous accessed widget.
	UPROPERTY( meta = ( BindWidget ) )
		UButton* BackButton;

	// The volume slider for the ambient sounds.
	UPROPERTY( meta = ( BindWidget ) )
		USlider* AmbientVolumeSlider;

	// The volume slider for the dialogue sounds.
	UPROPERTY( meta = ( BindWidget ) )
		USlider* DialogueVolumeSlider;

	// The volume slider for the master volume.
	UPROPERTY( meta = ( BindWidget ) )
		USlider* MasterVolumeSlider;

	// The volume slider for the music volume.
	UPROPERTY( meta = ( BindWidget ) )
		USlider* MusicVolumeSlider;

	// The volume slider for the SFX volume.
	UPROPERTY( meta = ( BindWidget ) )
		USlider* SFXVolumeSlider;

	// The toogle slider for the subtitles.
	UPROPERTY( meta = ( BindWidget ) )
		USlider* SubtitlesToggleSlider;

	// The text off that will change colour based on subtitle toggle
	UPROPERTY( meta = ( BindWidget ) )
		UTextBlock* OffText;

	// The text on that will change colour based on subtitle toggle
	UPROPERTY( meta = ( BindWidget ) )
		UTextBlock* OnText;

	// The sound mix class that will allow to override sound classes (audio channels) to change their volume
	UPROPERTY( Category = Audio, EditDefaultsOnly, BlueprintReadOnly )
		USoundMix* m_pcSoundMix;

	// The colour when the text is toggled off
	UPROPERTY( Category = Toggle, EditDefaultsOnly, BlueprintReadOnly )
		FColor m_pcToggledOffColour;

	// The colour when the text is toggled on
	UPROPERTY( Category = Toggle, EditDefaultsOnly, BlueprintReadOnly )
		FColor m_pcToggledOnColour;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: NativeConstruct() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: To intialise the sliders and load the save game file to apply the settings to the UI components
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void NativeConstruct() override;

private:
	// An array of all sliders to be populated so they can be easily recognisable with the volume settings float array.
	TArray<USlider*> m_paSliders;

	// The game instance that will retreive the save game file.
	URadianceGameInstance* m_pcGameInstance;

	// The save game file that will be overriden when saving new values.
	URadianceSaveGame* m_pcCurrentSaveGame;

	// The widget that accessed the options menu, so that it can go back to it.
	UUserWidget* m_pcPreviousAccessedWidget;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetVolumeForTheChannel( int iSliderID )
	// Author			: Nikodem Hamrol
	// Purpose			: To set the volume of audio channel that is recognised with the value of the slider.
	// Parameters		: The ID that recognises the slider.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetVolumeForTheChannel( int iSliderID );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ApplySettings()
	// Author			: Nikodem Hamrol
	// Purpose			: This function is used as delegate to the OnClick Apply Settings button. 
	//					,	To override the save game file with new values set, which are the volumes and toggle subtitles.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void ApplySettings();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BackToPreviousWindow()
	// Author			: Nikodem Hamrol
	// Purpose			: This function is used as delegate to the OnClick Back button.
	//					,	To go back to the previous window that the options menu was accessed from.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void BackToPreviousWindow();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: HighlightText( float fSliderValue )
	// Author			: Nikodem Hamrol
	// Purpose			: This function is used as delegate to the OnValueChanged toggle subtitles slider.
	//					,	To highlight text to respond to the toggle option.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void HighlightText( float fSliderValue );
};
