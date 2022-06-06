// Fill out your copyright notice in the Description page of Project Settings.

#include "RadianceGameInstance.h"

#include <Kismet/GameplayStatics.h>
#include <Sound/SoundMix.h>

#include "RadianceSaveGame.h"

URadianceGameInstance::URadianceGameInstance()
	: m_bHasGameStarted		(false)
	, m_bSaveFileExists		(false)
	, m_pcCurrentSaveGame	(nullptr)
{
	// Set the name of slot to the save game.
	m_sSaveGameNameSlot = FString( "SaveGame" );
}

bool URadianceGameInstance::CheckIfSaveGameExists()
{
	if( !m_bSaveFileExists )
	{
		// Check if the save game exists providing the save game slot name.
		if( UGameplayStatics::DoesSaveGameExist( m_sSaveGameNameSlot, 0 ) )
		{
			// Load the save game from slot.
			LoadSaveGameFromSlotName();

			m_bSaveFileExists = true;

			// Log that save game exists and return true as it exists.
			UE_LOG( LogTemp, Display, TEXT( "[URadianceGameInstance::CheckIfSacveGameExists] '%s' FILE EXISTS, AND LOADED" ), *m_sSaveGameNameSlot );

			// Stop the checking here.
			return true;
		}
		else
		{
			// Create a new save game slot and return true as it already exists.
			// After the save game got created, end the function.
			CreateNewSaveGameSlot();
			return true;
		}
	}

	return true;
}

void URadianceGameInstance::CreateNewSaveGameSlot()
{
	// Check if the save has been created yet.
	if( m_pcCurrentSaveGame == nullptr )
	{
		// Create a save game object using the custom save game made to save the game's data.
		USaveGame* NewGameSave = UGameplayStatics::CreateSaveGameObject( URadianceSaveGame::StaticClass() );

		// Check if the save game instance got created.
		if( NewGameSave != nullptr )
		{
			// Cast the created instane of the save game to initialise the current save game. Set the default audio settings.
			m_pcCurrentSaveGame = Cast<URadianceSaveGame>( NewGameSave );
			m_pcCurrentSaveGame->SetDefaultAudioSettings();

			m_bSaveFileExists = true;

			//Print the message that the save game has been created with default values
			UE_LOG( LogTemp, Display, TEXT( "[URadianceGameInstance::CreateNewSaveGameSlot] SAVE GAME CREATED AND SET THE DEFAULT VALUES" ) );
		}
	}

	// Save the game into the slot
	SaveGameInSlot();
}

void URadianceGameInstance::SaveGameInSlot()
{
	// Check if the current save game has been initialised
	if( m_pcCurrentSaveGame != nullptr )
	{
		// Save the game to slot using the current save game that has new data into the slot name, so it can be retrieved correctly.
		UGameplayStatics::SaveGameToSlot( m_pcCurrentSaveGame, m_sSaveGameNameSlot, 0 );

		//Print the message that the game has been saved.
		UE_LOG( LogTemp, Display, TEXT( "[URadianceGameInstance::SaveGameInSlot] GAME HAS BEEN SAVED TO '%s' SLOT" ), *m_sSaveGameNameSlot );
	}
}

void URadianceGameInstance::LoadSaveGameFromSlotName()
{
	// Create an instance of save game to load the save game file from the slot. 
	USaveGame* LoadedSaveGame = UGameplayStatics::LoadGameFromSlot( m_sSaveGameNameSlot, 0 );

	// Check if the loaded save game has been found and exists.
	if( LoadedSaveGame != nullptr )
	{
		// Set the save game from the found save game file.
		m_pcCurrentSaveGame = Cast<URadianceSaveGame>( LoadedSaveGame );

		// Print message that the save game got loaded correctly
		UE_LOG( LogTemp, Display, TEXT( "[URadianceGameInstance::LoadSaveGameFromSlotName] SUCCESSFULLY LOADED SAVE GAME FROM SLOT '%s'" ), *m_sSaveGameNameSlot );

		// Finish the function here.
		return;
	}
}

const bool URadianceGameInstance::GetSaveFileExists() const				{ return m_bSaveFileExists; }

void URadianceGameInstance::SetHasGameStarted( bool bHasGameStarted )	{ m_bHasGameStarted = bHasGameStarted; }

const bool URadianceGameInstance::GetHasGameStarted() const				{ return m_bHasGameStarted; }

URadianceSaveGame* URadianceGameInstance::GetRadianceSaveGame() const	{ return m_pcCurrentSaveGame; }
