// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RadianceGameInstance.generated.h"

// Forward class declarations
class URadianceSaveGame;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ADialogueManager
// Author				: Nikodem Hamrol
// Classes Inherited	: UGameInstance
// Purpose				: This class will handle the creation of the save game file, saving and, loading the game into the save 
//						,	slot.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API URadianceGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor Name	: URadianceGameInstance()
	// Author			: Nikodem Hamrol
	// Notes			: Sets up the components and default values.
	//----------------------------------------------------------------------------------------------------------------------------
	URadianceGameInstance();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SaveGameInSlot()
	// Author			: Nikodem Hamrol
	// Purpose			: This function will save the data in the save game class into the slot.
	//----------------------------------------------------------------------------------------------------------------------------
	void SaveGameInSlot();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CheckIfSaveGameExists()
	// Author			: Nikodem Hamrol
	// Purpose			: This function will check if the save game exists in the engine, which will create a new save game file
	//					,	if not found.
	// Returns			: A boolean that determines whether the save game exists.
	//----------------------------------------------------------------------------------------------------------------------------
	bool CheckIfSaveGameExists();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: LoadSaveGameFromSlotName()
	// Author			: Nikodem Hamrol
	// Purpose			: This function will load the save game file from the slot it was saved to and return it so that necessary
	//					,	classes can change the saved data for saving purposes.
	// Returns			: The save game class that will allow the data to be changed.
	//----------------------------------------------------------------------------------------------------------------------------
	void LoadSaveGameFromSlotName();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetSaveFileExists()
	// Author			: Nikodem Hamrol
	// Purpose			: This function will return the boolean that the save file does exist.
	// Returns			: A boolean that the save game does exist.
	//----------------------------------------------------------------------------------------------------------------------------
	const bool GetSaveFileExists() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetHasGameStarted( bool bHasGameStarted )
	// Author			: Nikodem Hamrol
	// Purpose			: This function will set the game started to prevent the splash screen.
	// Parameters		: A boolean that holds if the game has started first time.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetHasGameStarted( bool bHasGameStarted );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetHasGameStarted()
	// Author			: Nikodem Hamrol
	// Purpose			: This function will get the game started to check if the splash screen has played.
	// Parameters		: A boolean that holds if the game has started first time.
	//----------------------------------------------------------------------------------------------------------------------------
	const bool GetHasGameStarted() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetRadianceSaveGame()
	// Author			: Nikodem Hamrol
	// Purpose			: This function will return the save game class that has the current saved data. 
	// Returns			: The save game class holding saved options menu data.
	//----------------------------------------------------------------------------------------------------------------------------
	URadianceSaveGame* GetRadianceSaveGame() const;

private:
	// To check if the game has started for the first time.
	bool				m_bHasGameStarted;

	// To check if the save file exists.
	bool				m_bSaveFileExists;

	// The name of the save game slot, which is file name of the save file.
	FString				m_sSaveGameNameSlot;

	// The current save game instance that holds all the current saved data.
	UPROPERTY()
		URadianceSaveGame* m_pcCurrentSaveGame;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateNewSaveGameSlot()
	// Author			: Nikodem Hamrol
	// Purpose			: This function will create a new save game that will saved into the slot with a given name.
	//----------------------------------------------------------------------------------------------------------------------------
	void CreateNewSaveGameSlot();
};
