// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsMenuWidget.h"

#include <Components/Button.h>
#include <Components/CheckBox.h>
#include <Components/Slider.h>
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>
#include <Sound/SoundMix.h>

#include "Radiance/RadianceGameInstance.h"
#include "Radiance/RadianceSaveGame.h"

void UOptionsMenuWidget::NativeConstruct()
{
	// Call the native construct from the UUserWidget.
	Super::NativeConstruct();

	// Populate the Slider array.
	m_paSliders.Add( AmbientVolumeSlider );
	m_paSliders.Add( DialogueVolumeSlider );
	m_paSliders.Add( MusicVolumeSlider );
	m_paSliders.Add( SFXVolumeSlider );
	m_paSliders.Add( MasterVolumeSlider );

	// Get the custom game instance and which will return a game instance, which needs to be casted to the custom one.
	m_pcGameInstance = Cast<URadianceGameInstance>( UGameplayStatics::GetGameInstance( GetWorld() ) );

	// Check if the game instance was retrieved and check if the save file exists.
	if( m_pcGameInstance != nullptr )
	{
		// Set the sound mix in the gameplay statics using the sound mix class that was set in the blueprint.
		UGameplayStatics::SetBaseSoundMix( GetWorld(), m_pcSoundMix );

		if( m_pcGameInstance->CheckIfSaveGameExists() )
		{
			// Get the current save game that was loaded from the game instance.
			m_pcCurrentSaveGame = m_pcGameInstance->GetRadianceSaveGame();

			// Loop through all the sliders.
			for( int SliderID = 0; SliderID < m_paSliders.Num(); ++SliderID )
			{
				UE_LOG( LogTemp, Display, TEXT( "[UOptionsMenuWidget::ApplySettings] Volume: %f" ), m_pcCurrentSaveGame->GetVolumeInElement( SliderID ) );

				// Set the value of the slider by getting the volume from the save game file.
				m_paSliders[ SliderID ]->SetValue( m_pcCurrentSaveGame->GetVolumeInElement( SliderID ) );

				// Set volume for the channel, which corresponds to the slider in the current array element.
				SetVolumeForTheChannel( SliderID );
			}

			// Check whether the subtitles are displayed or not.
			if( m_pcCurrentSaveGame->GetSubtitlesDisplayed() )
			{
				// Set value of the slider to the max value if toggled on.
				SubtitlesToggleSlider->SetValue( SubtitlesToggleSlider->MaxValue );
				UE_LOG( LogTemp, Display, TEXT( "[UOptionsMenuWidget::ApplySettings] Its Toggled" ) )
			}
			else
			{
				// Set value of the slider to the min value if toggled off.
				SubtitlesToggleSlider->SetValue( SubtitlesToggleSlider->MinValue );
				UE_LOG( LogTemp, Display, TEXT( "[UOptionsMenuWidget::ApplySettings] Its Not Toggled" ) )
			}
		}

		// Highlight the text appropriate to the toggle.
		HighlightText( SubtitlesToggleSlider->GetValue() );
	}

	// Set on clicked function callback when the on click is triggered.
	ApplySettingsButton->	OnClicked.AddDynamic( this, &UOptionsMenuWidget::ApplySettings );
	BackButton->			OnClicked.AddDynamic( this, &UOptionsMenuWidget::BackToPreviousWindow );

	// Set on value changed function callback when the slider changed value.
	SubtitlesToggleSlider->	OnValueChanged.AddDynamic( this, &UOptionsMenuWidget::HighlightText );
}

void UOptionsMenuWidget::SetVolumeForTheChannel( int iSliderID )
{
	// Check if the slider ID is within the number of sliders in the array
	if( iSliderID < m_pcSoundMix->SoundClassEffects.Num() )
	{
		// Calculate the sound volume that will be set in audio engine. 
		// This is done by multiplying the master volume by the set channel volume.
		float VolumeToSet = m_paSliders[ iSliderID ]->GetValue() * m_pcCurrentSaveGame->GetMasterVolume();

		// Create a sound class to be the channel to override the sound mix for the volume.
		USoundClass* pcSoundClass = m_pcSoundMix->SoundClassEffects[ iSliderID ].SoundClassObject;

		// Override the sound mix class of the channel specified to change the volume.
		UGameplayStatics::SetSoundMixClassOverride( GetWorld(), m_pcSoundMix, pcSoundClass, VolumeToSet, 1.0f, 0.0f );
	}
}

void UOptionsMenuWidget::ApplySettings()
{
	// Set the Master volume to be saved
	float fMasterVolume = MasterVolumeSlider->GetValue();
	m_pcCurrentSaveGame->SetMasterVolume( fMasterVolume );

	// Check if the value of the subtitle slider is the Max value, so 1.0f (Toggled On).
	if( SubtitlesToggleSlider->GetValue() == SubtitlesToggleSlider->MaxValue )
	{
		// Save subtitles to be on.
		m_pcCurrentSaveGame->SetSubtitlesDisplayed( true );
		UE_LOG(LogTemp, Display, TEXT("[UOptionsMenuWidget::ApplySettings] Its Toggled %s"), *m_pcCurrentSaveGame->GetName() )
	}
	else
	{
		// Save subtitles to be off.
		m_pcCurrentSaveGame->SetSubtitlesDisplayed( false );
		UE_LOG( LogTemp, Display, TEXT( "[UOptionsMenuWidget::ApplySettings] Its Not Toggled %s" ), *m_pcCurrentSaveGame->GetName() )
	}

	// Loop throigh the sliders to save the volume of each audio channel.
	for( int SliderID = 0; SliderID < m_paSliders.Num(); ++SliderID )
	{
		// Set the volume of each audio channel to be saved.
		m_pcCurrentSaveGame->SetVolumeInElement( m_paSliders[ SliderID ]->GetValue(), SliderID );

		// Set the volume of each audio channel.
		SetVolumeForTheChannel( SliderID );
	}

	// Save the save game file as it has been changed.
	m_pcGameInstance->SaveGameInSlot();
}

void UOptionsMenuWidget::BackToPreviousWindow()
{
	// Hide the options menu and unhide the previous access widget.
	SetVisibility( ESlateVisibility::Hidden );
	m_pcPreviousAccessedWidget->SetVisibility( ESlateVisibility::Visible );
}

void UOptionsMenuWidget::HighlightText( float fSliderValue )
{
	// If the slider value is on max value (Toggled On)
	if( fSliderValue == SubtitlesToggleSlider->MaxValue )
	{
		// On text will highlight and Off text unhighlighted.
		OnText->SetColorAndOpacity	( FSlateColor( m_pcToggledOnColour ) );
		OffText->SetColorAndOpacity	( FSlateColor( m_pcToggledOffColour ) );
	}
	else
	{
		// Off text will highlight and On text unhighlighted.
		OnText->SetColorAndOpacity	( FSlateColor( m_pcToggledOffColour ) );
		OffText->SetColorAndOpacity	( FSlateColor( m_pcToggledOnColour ) );
	}
}

void UOptionsMenuWidget::SetPreviousAccessedWidget( UUserWidget* pcPreviousAccessedWidget ) { m_pcPreviousAccessedWidget = pcPreviousAccessedWidget; }
