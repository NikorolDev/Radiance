// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct_DialogueSequence.h"
#include "DialogueManager.generated.h"

// Forward class declarations
class UAudioComponent;
class UBillboardComponent;


class UDialogueWidget;
class URadianceGameInstance;
class URadianceSaveGame;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ADialogueManager
// Author				: Nikodem Hamrol
// Classes Inherited	: AActor
// Purpose				: This class will hold all the dialogue and display the correct sequence onto the widget within a 
//						,	level.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ADialogueManager : public AActor
{
	GENERATED_BODY()

public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor Name	: ADialogueManager()
	// Author			: Nikodem Hamrol
	// Notes			: Sets up the components and default values.
	//----------------------------------------------------------------------------------------------------------------------------
	ADialogueManager();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Tick( float DeltaTime ) override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Parameters		: DeltaTime - The elapsed time from previous tick function call
	// Purpose			: To check if the dialogue sequence has been intitialised so it can play it
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void Tick( float DeltaTime ) override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: InitialiseDialogueSequence( FString& rsDialogueID )
	// Author			: Nikodem Hamrol
	// Parameters		: rsDialogueID - The identifier for the dialogue.
	// Purpose			: Initialise the dialogue sequence when the player steps into the trigger volume.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION( Category= Dialogue, BlueprintCallable  )
		void InitialiseDialogueSequence( const FString& rsDialogueID );

protected:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: To create the widget and add it to viewport.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

private:
#pragma region Private Variables (not exposed to the editor)
	// To check if the dialogue squence has been initilaised.
	bool											m_bIsDialogueSequenceInitialised;

	// The current time of the dialogue term in sequence.
	float											m_fCurrentDialogueTermTime;

	// The duration of the current dialogue term.
	float											m_fCurrentDialogueDuration;

	// The elapsed time from previous tick call.
	float											m_fDeltaTime;

	// The maximum number of elements in the array of the curent dialogue sequence.
	int												m_iCurrentNumberOfDialoguesInSequence;

	// To access the text and the duration of display in the current dialogue sequence.
	int												m_iDialogueID;

	// An instance of the dialogue sequence, to be used when the dialogue sequence is played.
	FStructDialogueSequence*						m_pfsDialogueSequence;

	// The dialogue widget that is used to display onto the screen and change text of the text block component
	// to show the right dialogue.
	UDialogueWidget*								m_pcDialogueWidget;

	// The game instance reference to get the saved options value for subtitles.
	URadianceGameInstance*							m_pcGameInstance;

	// The current save game instance that holds all the current saved data to grab the boolean option for subtitles.
	URadianceSaveGame*								m_pcCurrentSaveGame;

#pragma endregion

#pragma region Private Variables (exposed to the editor)
	// An audio component that will play the dialogue volume instead of using gameplay statics
	UPROPERTY( Category = Audio, EditDefaultsOnly, meta = ( DisplayName = "Audio Component" ) )
		UAudioComponent*							m_pcAudioComponent;

	// This billboard will visualise the manager in the map editor.
	UPROPERTY( Category = Components, EditDefaultsOnly, meta = ( DisplayName = "Dialogue Manager Billboard" ) )
		UBillboardComponent*						m_pcDialogueManagerBillboard;

	// This dialogue table will hold all the dialogue in the level.
	UPROPERTY( Category = Dialogue, EditInstanceOnly, meta = ( DisplayName = "Dialogue" ) )
		TMap<FString, FStructDialogueSequence>		m_tmDialogueTable;

	// This is the sub class of the desired widget to be used to display the dialogue.
	// MAKE SURE TO USE THE BPW_DIALOGUEWIDGET.
	UPROPERTY( Category = Dialogue, EditInstanceOnly, meta = ( DisplayName = "Dialogue Widget" ) )
		TSubclassOf<UDialogueWidget>				m_ptcDialogueWidget;

#pragma endregion

#pragma region Private Functions
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: PlayDialogueSequence()
	// Author			: Nikodem Hamrol
	// Purpose			: To play the dialogue sequence when initialised.
	//----------------------------------------------------------------------------------------------------------------------------
	void PlayDialogueSequence();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetDialogueTerm( USoundWave* pcDialogueAudio, FString* psDialogueText, float fDialogueDurationOffset )
	// Author			: Nikodem Hamrol
	// Purpose			: To set the dialogue term to be played. To also check if dialogue audio is included and dialogue text.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetDialogueTerm();

#pragma endregion
};
