// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueManager.h"

#include <Components/AudioComponent.h>
#include <Components/BillboardComponent.h>
#include <Kismet/GameplayStatics.h>

#include "DialogueWidget.h"
#include "Radiance/RadianceGameInstance.h"
#include "Radiance/RadianceSaveGame.h"

ADialogueManager::ADialogueManager()
	: m_bIsDialogueSequenceInitialised		(false)
	, m_fCurrentDialogueTermTime			(0.0f)
	, m_fCurrentDialogueDuration			(0.0f)
	, m_fDeltaTime							(0.0f)
	, m_iCurrentNumberOfDialoguesInSequence	(0)
	, m_iDialogueID							(0)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and setup...
	// Billboard Component (m_pcDialogueManagerBillboard).
	m_pcDialogueManagerBillboard = CreateDefaultSubobject<UBillboardComponent>( TEXT( "DialogueManagerDisplay" ) );
	RootComponent = m_pcDialogueManagerBillboard;

	// Audio Component (m_pcAudioComponent).
	m_pcAudioComponent = CreateDefaultSubobject<UAudioComponent>( TEXT( "Audio Component" ) );
	m_pcAudioComponent->SetupAttachment( m_pcDialogueManagerBillboard );

	// Find the icon of the dialogue manager using the asset address reference in the engine.
	static ConstructorHelpers::FObjectFinder<UTexture2D> DialogueIcon( TEXT( "/Game/Radiance/Icons/T_Icon_DialogueManager.T_Icon_DialogueManager" ) );

	// Check if the icon was found.
	if( DialogueIcon.Succeeded() )
	{
		// Set the sprite of the billboard.
		m_pcDialogueManagerBillboard->SetSprite( DialogueIcon.Object );
	}
}

void ADialogueManager::BeginPlay()
{
	// Call the base class's begin play function, which would be from AActor class.
	Super::BeginPlay();

	// Create a widget from the subclass of the widget, which should be "BPW_DialogueWidget". This initialises the private 
	// instance of the widget.
	// Get the player controller as a correct reference to create the widget.
	// Then add the widget to viewport.
	m_pcDialogueWidget = CreateWidget<UDialogueWidget>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ), 
														m_ptcDialogueWidget );

	if( m_pcDialogueWidget != nullptr )
	{
		m_pcDialogueWidget->AddToViewport();
	}
	else
	{
		UE_LOG( LogTemp, Display, TEXT( "Widget Exists" ) );
	}

	// Get the set custom game instance. This is to get boolean value of displaying subtitles.
	m_pcGameInstance = Cast<URadianceGameInstance>( UGameplayStatics::GetGameInstance( GetWorld() ) );
	
	// Check if the game instance was retrieved correctly.
	if( m_pcGameInstance != nullptr )
	{
		// Check if the save game file exists.
		if( m_pcGameInstance->CheckIfSaveGameExists() )
		{
			// Get the save game file to check whether the subtitles are enabled.
			m_pcCurrentSaveGame = m_pcGameInstance->GetRadianceSaveGame();
			UE_LOG( LogTemp, Display, TEXT( "[ADialogueManager::BeginPlay] GOT SAVE GAME %s" ), *m_pcCurrentSaveGame->GetName() );
		}
		else
		{
			UE_LOG( LogTemp, Display, TEXT( "[ADialogueManager::BeginPlay] BROKE" ) );
		}
	}
}

void ADialogueManager::Tick( float DeltaTime )
{
	// Call the base class's tick function, which would be from AActor class.
	Super::Tick( DeltaTime );

	// Set the delta so it can be used across this class.
	m_fDeltaTime = DeltaTime;

	// If the dialogue has been initialised
	if( m_bIsDialogueSequenceInitialised )
	{
		// Play the dialogue sequence.
		PlayDialogueSequence();
	}
}

void ADialogueManager::PlayDialogueSequence()
{
	// Increment the dialogue display time by deltaTime to delay the switch to next dialogue text.
	m_fCurrentDialogueTermTime += m_fDeltaTime;

	// Check if the dialogue term time has been delayed enough based on the specified duration.
	if( m_fCurrentDialogueTermTime >= m_fCurrentDialogueDuration )
	{
		// Decrement the time by the set duration to not waste extra delta seconds.
		m_fCurrentDialogueTermTime -= m_fCurrentDialogueDuration;

		// Increment the text ID for it to play the next dialogue in the sequence.
		m_iDialogueID++;

		// Check if there is more dialogue by checking if the dialogue ID is less than 
		// the amount of dialogues in the sequence.
		if( m_iDialogueID < m_iCurrentNumberOfDialoguesInSequence )
		{
			// Set the next dialogue term.
			SetDialogueTerm();
		}
		else
		{
			// Uninitialise by hiding the dialogue widget and setting the bool to false so 
			// the next dialogue sequence can be initialised.
			m_pcDialogueWidget->HideDialogue();
			m_bIsDialogueSequenceInitialised = false;
		}
	}
}

void ADialogueManager::SetDialogueTerm()
{
	// Make a local variable to set the dialogue sequence
	FStructDialogueProperties* dialogueSequence = &m_pfsDialogueSequence->DialogueSequence[ m_iDialogueID ];

	// Check if the dialogue text is filled.
	if( !dialogueSequence->DialogueText.IsEmpty() )
	{
		// Check if the subtitles option is enabled.
		if( m_pcCurrentSaveGame->GetSubtitlesDisplayed() )
		{
			UE_LOG( LogTemp, Warning, TEXT( "[ADialogueManager::SetDialogueTerm] Subtitles displayed" ) );

			// Display the current dialogue text.
			m_pcDialogueWidget->DisplayText( dialogueSequence->CharacterName, dialogueSequence->DialogueText );
		}
		else
		{
			UE_LOG( LogTemp, Warning, TEXT( "[ADialogueManager::SetDialogueTerm] Subtitles should not display" ) );

			// Otherwise, do another check to see if the dialogue widget is currently visible.
			if( m_pcDialogueWidget->GetIsVisible() )
			{
				// If so, hide the dialogue widget.
				m_pcDialogueWidget->HideDialogue();
			}
		}
	}
	else
	{
		// Print a message onto the screen and into the output log if there is no dialogue text
		UE_LOG( LogTemp, Warning,
			TEXT( "NO DIALOGUE TEXT TO DISPLAY | MISSING DATA IN THE DIALOGUE SEQUENCE | MISSING DIALOGUE TEXT" ) );
		GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red,
			TEXT( "NO DIALOGUE TEXT TO DISPLAY | MISSING DATA IN THE DIALOGUE SEQUENCE | MISSING DIALOGUE TEXT" ) );
	}

	//Check if the dialogue audio selected has been set in the editor.
	if( dialogueSequence->DialogueAudio != nullptr )
	{
		// Set the dialogue term duration, using the duration offset and the duration of the audio file.
		m_fCurrentDialogueDuration = dialogueSequence->DialogueDurationOffset + dialogueSequence->DialogueAudio->GetDuration();
	
		// Use the audio component to set the dialogue audio to play and play it.
		// Replaced the use of gameplay statics as the audio component gives more control of the audio being played.
		m_pcAudioComponent->SetSound( dialogueSequence->DialogueAudio );
		m_pcAudioComponent->Play();
	}
	else
	{
		// Print a message onto the screen and into the output log if there is no dialogue text
		UE_LOG( LogTemp, Warning,
			TEXT( "NO DIALOGUE AUDIO TO PLAY | MISSING DATA IN THE DIALOGUE SEQUENCE | MISSING DIALOGUE AUDIO" ) );
		GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red,
			TEXT( "NO DIALOGUE AUDIO TO PLAY | MISSING DATA IN THE DIALOGUE SEQUENCE | MISSING DIALOGUE AUDIO" ) );
	}
}

void ADialogueManager::InitialiseDialogueSequence( const FString& rsDialogueID )
{
	// Reset the dialogue ID to 0, to get the first dialogue text in the array.
	// Reset the dialogue term time to 0 and find the correct dialogue in the map.
	m_iDialogueID = 0;
	m_fCurrentDialogueTermTime = 0.0f;
	m_pfsDialogueSequence = m_tmDialogueTable.Find( rsDialogueID );

	// Check if the dialogue sequence was found.
	if( m_pfsDialogueSequence != nullptr )
	{
		// Now that the array is filled up with a new dialogue sequence. 
		// Set the max amount in the current dialogue sequence. This is to mark the end of the dialogue sequence.
		m_iCurrentNumberOfDialoguesInSequence = m_pfsDialogueSequence->DialogueSequence.Num();
	
		// Dialogue sequence is now initialised. The boolean is set here, because it has to pass a check 
		// in the "SetDialogueTerm" function to see if the audio and text are set for the intial dialogue term in the sequence.
		m_bIsDialogueSequenceInitialised = true;
	
		// Set the initial dialogue term.
		SetDialogueTerm();
	}
	else
	{
		// Print a message onto the screen and on the output log if the dialogue sequence could not be found.
		UE_LOG( LogTemp, Warning,
			TEXT( "NO DIALOGUE FOUND | NONE MATCHING DATA ON THE TRIGGER VOLUME OR DIALOGUE MANAGER | POTENTIAL TYPO IN THE IDS" ) );
		GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red,
			TEXT( "NO DIALOGUE FOUND | NONE MATCHING DATA ON THE TRIGGER VOLUME OR DIALOGUE MANAGER | POTENTIAL TYPO IN THE IDS" ) );
	}
}
