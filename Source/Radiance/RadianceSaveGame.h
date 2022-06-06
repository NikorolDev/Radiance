// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RadianceSaveGame.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: URadianceSaveGame
// Author				: Nikodem Hamrol
// Classes Inherited	: USaveGame
// Purpose				: This class is will hold the values that will be saved in a save file that will be handled in
//						,	URadianceGameInstance. It will have basic functionality to reset the values to default.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API URadianceSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor Name	: URadianceSaveGame()
	// Author			: Nikodem Hamrol
	// Notes			: Sets up the components and default values.
	//----------------------------------------------------------------------------------------------------------------------------
	URadianceSaveGame();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetDefaultAudioSettings()
	// Author			: Nikodem Hamrol
	// Purpose			: This will set all audio channel's volume to default, which will be max volume.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetDefaultAudioSettings();

#pragma region Getters and Setters for Audio Settings
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetAmbientVolume( float fAmbientVolume )
	// Author			: Nikodem Hamrol
	// Purpose			: This will set the volume for ambient sounds.
	// Parameters		: fAmbientVolume - The desired volume for ambient sounds.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetAmbientVolume( float fAmbientVolume );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetAmbientVolume()
	// Author			: Nikodem Hamrol
	// Purpose			: This will return the volume for ambient sounds.
	// Returns			: The current set volume for ambient sounds.
	//----------------------------------------------------------------------------------------------------------------------------
	const float GetAmbientVolume() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetDialogueVolume( float fDialogueVolume )
	// Author			: Nikodem Hamrol
	// Purpose			: This will set the volume for dialogue voice overs.
	// Parameters		: fDialogueVolume - The desired volume for dialogue voice overs.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetDialogueVolume( float fDialogueVolume );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetDialogueVolume()
	// Author			: Nikodem Hamrol
	// Purpose			: This will return the volume fordialogue voice overs.
	// Returns			: The current set volume for dialogue voice overs.
	//----------------------------------------------------------------------------------------------------------------------------
	const float GetDialogueVolume() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetMasterVolume( float fMasterVolume )
	// Author			: Nikodem Hamrol
	// Purpose			: This will set the volume for master.
	// Parameters		: fMasterVolume - The desired volume for master.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetMasterVolume( float fMasterVolume );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetAmbientVolume()
	// Author			: Nikodem Hamrol
	// Purpose			: This will return the volume for master.
	// Returns			: The current set volume for master.
	//----------------------------------------------------------------------------------------------------------------------------
	const float GetMasterVolume() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetMusicVolume( float fMusicVolume )
	// Author			: Nikodem Hamrol
	// Purpose			: This will set the volume for music.
	// Parameters		: fMusicVolume - The desired volume for music.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetMusicVolume( float fMusicVolume );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetAmbientVolume()
	// Author			: Nikodem Hamrol
	// Purpose			: This will return the volume for music.
	// Returns			: The current set volume for music.
	//----------------------------------------------------------------------------------------------------------------------------
	const float GetMusicVolume() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetSFXVolume( float fSFXVolume )
	// Author			: Nikodem Hamrol
	// Purpose			: This will set the volume for sound effects.
	// Parameters		: fSFXVolume - The desired volume for sound effects.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetSFXVolume( float fSFXVolume );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetAmbientVolume()
	// Author			: Nikodem Hamrol
	// Purpose			: This will return the volume for sound effects.
	// Returns			: The current set volume for sounds effects.
	//----------------------------------------------------------------------------------------------------------------------------
	const float GetSFXVolume()const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetVolumeInElement( float fVolume, int iVolumeID );
	// Author			: Nikodem Hamrol
	// Purpose			: This function will set the volume in the required element. This is intended to be used in for loops 
	//					,	only. There are setters for specific audio channels.
	// Parameters		: fVolume	- The desired volume for the element.
	//					, iVolumeID	- The array element to set the volume to.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetVolumeInElement( float fVolume, int iVolumeID );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetVolumeInElement( int VolumeID )
	// Author			: Nikodem Hamrol
	// Purpose			: This will return the audio volume in the required element. This is intended to be used in for loops 
	//					,	only. There are getters for specific audio channels.
	// Parameters		: iVolumeID - The array element to retrieve the volume from.
	// Returns			: The volume of the audio channel needed to be returned using the VolumeID.
	//----------------------------------------------------------------------------------------------------------------------------
	const float GetVolumeInElement( int VolumeID );

#pragma endregion

#pragma region Getters and Setters for Display Settings

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetVolumeInElement( float fVolume, int iVolumeID );
	// Author			: Nikodem Hamrol
	// Purpose			: This function will set the boolean to display subtitles .
	// Parameters		: bAreSubtitlesDisplayed	- Whether to display subtitles or not
	//----------------------------------------------------------------------------------------------------------------------------
	void SetSubtitlesDisplayed( bool bAreSubtitlesDisplayed );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetVolumeInElement( int VolumeID )
	// Author			: Nikodem Hamrol
	// Purpose			: This will return the audio volume in the required element. This is intended to be used in for loops 
	//					,	only. There are getters for specific audio channels.
	// Parameters		: iVolumeID - The array element to retrieve the volume from.
	// Returns			: The volume of the audio channel needed to be returned using the VolumeID.
	//----------------------------------------------------------------------------------------------------------------------------
	const bool GetSubtitlesDisplayed() const;

#pragma endregion

private:
	// The default audio volume setting.
	float m_fDefaultAudioVolume;

	// The max number of audio settings needed.
	int m_iMaxNumberOfAudioSettings;

	// The option for subtitles to be on or off.
	UPROPERTY()
		bool m_bAreSubtitlesDispalyed;

	// Array of all audio settings that are saved in this save slot.
	UPROPERTY()
		TArray<float> m_afVolumes;
};
