// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_EndGame.h"

#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include <LevelSequence.h>
#include <LevelSequenceActor.h>
#include <LevelSequencePlayer.h>

#include "Radiance/LoopManager.h"
#include "Radiance/Menus/SplashSceneWidget.h"
#include "Radiance/MainMenuGameMode.h"

ATriggerVolume_EndGame::ATriggerVolume_EndGame()
{
}

void ATriggerVolume_EndGame::BeginPlay()
{
	// Call the base class's begin play function, which would be the AActor's one as the TriggerVolume_Base does not have one.
	Super::BeginPlay();

	// Create default sequence playback settings.
	FMovieSceneSequencePlaybackSettings m_pfsLevelSequencePlaybackSettings;

	// Create the sequence player to be played when the player enters the trigger volume.
	m_pcLevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer( GetWorld(), m_pcFinalCutscene->GetSequence(), 
								m_pfsLevelSequencePlaybackSettings, m_pcFinalCutscene);

	// Get the loop manager that is in the level.
	m_pcLoopManager = Cast<ALoopManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ALoopManager::StaticClass() ) );

	// Setup an OnComponentBeginOverlap callback function to be called when an overlap is triggered.
	m_BoxTriggerVolume->OnComponentBeginOverlap.AddDynamic( this, &ATriggerVolume_EndGame::OnBeginOverlapTrigger );
}

void ATriggerVolume_EndGame::OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit )
{
	// Check if the actor is not another TriggerVolume_EndGame and if the actor contains a tag of player.
	// This will detect the player if it has that tag.
	if( ( OtherActor != this ) && OtherActor->Tags.Contains( "Player" ) )
	{
		// Turn off collision. To not be called again.
		m_BoxTriggerVolume->SetCollisionEnabled( ECollisionEnabled::NoCollision );

		// Call this function, which will stop the loop and stop the timers
		m_pcLoopManager->GameWon();

		// Then play the final cutscene.
		m_pcLevelSequencePlayer->Play();
	}
}
