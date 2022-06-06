// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerVolume_Ambience.h"

#include <Components/AudioComponent.h>
#include <Components/BoxComponent.h>

ATriggerVolume_Ambience::ATriggerVolume_Ambience()
{
	// Create and setup...
	// Audio Component (m_pcAudioComponent).
	m_pcAudioComponent = CreateDefaultSubobject<UAudioComponent>( TEXT( "AudioComponent" ) );
	m_pcAudioComponent->SetupAttachment( m_BoxTriggerVolume );
}

void ATriggerVolume_Ambience::BeginPlay()
{
	// Call the base class's begin play function, which would be the AActor's one as the TriggerVolume_Base does not have one.
	Super::BeginPlay();

	// Check if the sound file has been set in the editor
	if( m_pcAmbientSound != nullptr )
	{
		// Set the sound to play
		m_pcAudioComponent->SetSound( m_pcAmbientSound );
	}
	else
	{
		// Print a message in the output log and in the print the message onto the screen that no ambient sound was set in the editor.
		UE_LOG( LogTemp, Error,
			TEXT( "AMBIENT SOUND COULD NOT BE SET | MISSING DATA IN THE AMBIENT TRIGGER VOLUME" ) );
		GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red,
			TEXT( "AMBIENT SOUND COULD NOT BE SET | MISSING DATA IN THE AMBIENT TRIGGER VOLUME" ) );
	}

	// Setup an OnComponentBeginOverlap and OnComponentEndOverlap callback functions to be called when an overlap 
	// begin and end is triggered.
	m_BoxTriggerVolume->OnComponentBeginOverlap.AddDynamic( this, &ATriggerVolume_Ambience::OnBeginOverlapTrigger );
	m_BoxTriggerVolume->OnComponentEndOverlap.AddDynamic( this, &ATriggerVolume_Ambience::OnEndOverlapTrigger );
}

void ATriggerVolume_Ambience::OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit )
{
	// Check if the actor is not another TriggerVolume_Ambience and if the actor contains a tag of player.
	// This will detect the player if it has that tag.
	if( ( OtherActor != this ) && OtherActor->Tags.Contains( "Player" ) )
	{
		// Play the ambient sound and fade it in with a desired fade in duration.
		m_pcAudioComponent->FadeIn( m_fFadeInDuration );
	}
}

void ATriggerVolume_Ambience::OnEndOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex )
{
	if( ( OtherActor->Tags.Contains( "Player" ) ) )
	{
		// Fade out the ambient sound and stop playingwith a desired fade out duration.
		m_pcAudioComponent->FadeOut( m_fFadeOutDuration, 0.0f );
	}
}
