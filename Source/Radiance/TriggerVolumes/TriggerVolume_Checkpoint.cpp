// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_Checkpoint.h"
#include "Kismet/GameplayStatics.h"
#include "Radiance/RadianceCharacter.h"

#include <Components/BoxComponent.h>

ATriggerVolume_Checkpoint::ATriggerVolume_Checkpoint()
	: m_bHasBeenTriggered(false)
{
}

void ATriggerVolume_Checkpoint::BeginPlay()
{
	// Call the base class's begin play function, which would be the AActor's one as the TriggerVolume_Base does not have one.
	Super::BeginPlay();

	// Setup an OnComponentBeginOverlap callback function to be called when an overlap is triggered.
	m_BoxTriggerVolume->OnComponentBeginOverlap.AddDynamic( this, &ATriggerVolume_Checkpoint::OnBeginOverlapTrigger );
}

void ATriggerVolume_Checkpoint::OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit )
{
	if( ( OtherActor != this ) && OtherActor->Tags.Contains( "Player" ) )
	{

		m_bHasBeenTriggered = true;

		//USaveState_Game* mSave = Cast<USaveState_Game> ( UGameplayStatics::CreateSaveGameObject ( USaveState_Game::StaticClass ( ) ) );

		//mSave->PlayerLocation = OtherActor->GetActorLocation ( );

		//mSave->m_iLevelID++;
		

		GEngine->AddOnScreenDebugMessage (-1, 5.0f, FColor::Orange, TEXT ( "UPDATE STATE" ));

		//UGameplayStatics::SaveGameToSlot( mSave, TEXT ( "SaveSlot" ), 0 );

		GEngine->AddOnScreenDebugMessage (-1, 5.0f, FColor::Green, TEXT ( "SAVE" ) );
	}
}
