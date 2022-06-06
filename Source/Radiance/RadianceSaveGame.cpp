// Fill out your copyright notice in the Description page of Project Settings.

#include "RadianceSaveGame.h"

URadianceSaveGame::URadianceSaveGame()
	: m_fDefaultAudioVolume			(1.0f)
	, m_iMaxNumberOfAudioSettings	(5)
{
}

void URadianceSaveGame::SetDefaultAudioSettings()
{
	// Set other values individually.
	m_bAreSubtitlesDispalyed = true;

	// Check if the array has any entries
	if( m_afVolumes.Num() == m_iMaxNumberOfAudioSettings )
	{
		// If entries were found, reset the audio volume values to default
		for( int AudioID = 0; AudioID < m_iMaxNumberOfAudioSettings; AudioID++ )
		{
			// Set the element (Volume) in the array to default
			m_afVolumes[ AudioID ] = m_fDefaultAudioVolume;
		}

		// Print message that the audio volumes have been reset to defualt
		UE_LOG( LogTemp, Display, TEXT( "RESET ALL AUDIO CHANNEL VOLUME TO THEIR DEFAULT VALUES" ) );
	}
	else
	{
		// If there are no entries, the array will be initialised to add 5 audio settings and set to be 
		m_afVolumes.Init( m_fDefaultAudioVolume, m_iMaxNumberOfAudioSettings );
		UE_LOG( LogTemp, Display, TEXT( "INITIALISED AUDIO VOLUMES FOR THE FIRST TIME" ) );
	}
}

#pragma region Getters and Setters for Audio Settings
void URadianceSaveGame::SetAmbientVolume( float fAmbientVolume )				{ m_afVolumes[ 0 ] = fAmbientVolume; }

const float URadianceSaveGame::GetAmbientVolume() const							{ return m_afVolumes[ 0 ]; }

void URadianceSaveGame::SetDialogueVolume( float fDialogueVolume )				{ m_afVolumes[ 1 ] = fDialogueVolume; }

const float URadianceSaveGame::GetDialogueVolume() const						{ return m_afVolumes[ 1 ]; }

void URadianceSaveGame::SetMasterVolume( float fMasterVolume )					{ m_afVolumes[ 4 ] = fMasterVolume; }

const float URadianceSaveGame::GetMasterVolume() const							{ return m_afVolumes[ 4 ]; }

void URadianceSaveGame::SetMusicVolume(float fMusicVolume)						{ m_afVolumes[ 2 ] = fMusicVolume; }

const float URadianceSaveGame::GetMusicVolume() const							{ return m_afVolumes[ 2 ]; }

void URadianceSaveGame::SetSFXVolume( float fSFXVolume )						{ m_afVolumes[ 3 ] = fSFXVolume; }

const float URadianceSaveGame::GetSFXVolume() const								{ return m_afVolumes[ 3 ]; }

void URadianceSaveGame::SetVolumeInElement( float fVolume, int iVolumeID )		{ m_afVolumes[ iVolumeID ] = fVolume; }

const float URadianceSaveGame::GetVolumeInElement( int VolumeID )				{ return m_afVolumes[VolumeID]; }

#pragma endregion

#pragma region Getters and Setters for Display Settings
void URadianceSaveGame::SetSubtitlesDisplayed( bool bAreSubtitlesDisplayed )	{ m_bAreSubtitlesDispalyed = bAreSubtitlesDisplayed; }

const bool URadianceSaveGame::GetSubtitlesDisplayed() const						{ return m_bAreSubtitlesDispalyed; }

#pragma endregion
