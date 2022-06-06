// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerVolume_Dialogue.h"

#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>

#include "Radiance/Dialogue/DialogueManager.h"

ATriggerVolume_Dialogue::ATriggerVolume_Dialogue()
	: m_bHasBeenTriggered(false)
{
}

void ATriggerVolume_Dialogue::BeginPlay()
{
	// Call the base class's begin play function, which would be the AActor's one as the TriggerVolume_Base does not have one.
	Super::BeginPlay();

	// Get the dialogue manager that is in the level.
	m_pcDialogueManager = Cast<ADialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ADialogueManager::StaticClass() ) );

	if( m_pcDialogueManager == nullptr )
	{
		// Log that the dialogue manager is missing.
		UE_LOG( LogTemp, Error,
			TEXT( "MISSING DIALOGUE MANAGER IN THE LEVEL | DIALOGUE WILL NOT INITIALISE | ADD DIALOGUE MANAGER TO THE LEVEL UNDER 'C++CLASSES/RADIANCE/DIALOGUE" ) );
		GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red,
			TEXT( "MISSING DIALOGUE MANAGER IN THE LEVEL | DIALOGUE WILL NOT INITIALISE | ADD DIALOGUE MANAGER TO THE LEVEL UNDER 'C++CLASSES/RADIANCE/DIALOGUE" ) );
	}

	// Setup an OnComponentBeginOverlap callback function to be called when an overlap is triggered.
	m_BoxTriggerVolume->OnComponentBeginOverlap.AddDynamic( this, &ATriggerVolume_Dialogue::OnBeginOverlapTrigger );
}

void ATriggerVolume_Dialogue::OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit )
{
	// Check if this trigger volume instance has already been triggered.
	// Check if the actor is not another TriggerVolume_Dialogue and if the actor contains a tag of player.
	// This will detect the player if it has that tag.
	if( ( !m_bHasBeenTriggered ) && ( OtherActor != this ) && OtherActor->Tags.Contains( "Player" ) )
	{
		if( m_pcDialogueManager != nullptr )
		{
			// Set the trigger boolean to true and disable collision.
			// This is so the same dialogue won't be initialised again and the physics engine will now ignore this trigger volume
			m_bHasBeenTriggered = true;
			m_BoxTriggerVolume->SetCollisionEnabled( ECollisionEnabled::NoCollision );

			// Initialise the dialogue sequence using the ID specified for this dialogue trigger.
			m_pcDialogueManager->InitialiseDialogueSequence( m_sDialogueID );
		}
		else
		{
			// Log that the dialogue manager is missing.
			UE_LOG( LogTemp, Error,
				TEXT( "MISSING DIALOGUE MANAGER IN THE LEVEL | FAILED TO INITIALISE DIALOGUE | ADD DIALOGUE MANAGER TO THE LEVEL UNDER 'C++CLASSES/RADIANCE/DIALOGUE" ) );
			GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red,
				TEXT( "MISSING DIALOGUE MANAGER IN THE LEVEL | FAILED TO INITIALISE DIALOGUE | ADD DIALOGUE MANAGER TO THE LEVEL UNDER 'C++CLASSES/RADIANCE/DIALOGUE" ) );
		}
	}
}
