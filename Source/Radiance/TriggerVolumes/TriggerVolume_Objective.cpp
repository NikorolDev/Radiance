// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_Objective.h"

#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>

#include "Radiance/Inventory/InventoryManager.h"

ATriggerVolume_Objective::ATriggerVolume_Objective()
	: m_bHasBeenTriggered(false)
{
}

void ATriggerVolume_Objective::BeginPlay()
{
	// Call the base class's begin play function, which would be the AActor's one as the TriggerVolume_Base does not have one.
	Super::BeginPlay();

	// Get the inventory manager that is in the level.
	m_pcInventoryManager = Cast<AInventoryManager>( UGameplayStatics::GetActorOfClass( GetWorld(), AInventoryManager::StaticClass() ) );

	// Check if the inventory manager got accessed and is in the level.
	if( m_pcInventoryManager == nullptr )
	{
		// Log that the inventory manager is missing.
		UE_LOG( LogTemp, Error,
			TEXT( "MISSING INVENTORY MANAGER IN THE LEVEL | OBJECTIVE POP-UP WILL NOT BE DISPLAYED | ADD INVENTORY MANAGER TO THE LEVEL UNDER 'C++CLASSES/RADIANCE/INVENTORY" ) );
		GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red,
			TEXT( "MISSING INVENTORY MANAGER IN THE LEVEL | OBJECTIVE POP-UP WILL NOT BE DISPLAYED | ADD INVENTORY MANAGER TO THE LEVEL UNDER 'C++CLASSES/RADIANCE/INVENTORY" ) );
	}

	// Setup an OnComponentBeginOverlap callback functions to be called when an overlap begin  is triggered.
	m_BoxTriggerVolume->OnComponentBeginOverlap.AddDynamic( this, &ATriggerVolume_Objective::OnBeginOverlapTrigger );
}

void ATriggerVolume_Objective::OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit )
{
	// Check if the actor is not another TriggerVolume_Objective and if the actor contains a tag of player.
	// This will detect the player if it has that tag.
	if( ( !m_bHasBeenTriggered ) && ( OtherActor != this ) && OtherActor->Tags.Contains( "Player" ) )
	{
		// Check if the inventory manager is in the level
		if( m_pcInventoryManager != nullptr )
		{
			// Display the pop-up element and the trigger volume won't triggered anymore, by setting the boolean and turning off the collision
			m_bHasBeenTriggered = true;
			m_BoxTriggerVolume->SetCollisionEnabled( ECollisionEnabled::NoCollision );
			m_pcInventoryManager->AddItem( m_sObjectiveID, 1 );
		}
		else
		{
			// Log that the inventory manager is missing.
			UE_LOG( LogTemp, Error,
				TEXT( "MISSING INVENTORY MANAGER IN THE LEVEL | OBJECTIVE POP-UP WILL NOT BE DISPLAYED | ADD INVENTORY MANAGER TO THE LEVEL UNDER 'C++CLASSES/RADIANCE/INVENTORY" ) );
			GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red,
				TEXT( "MISSING INVENTORY MANAGER IN THE LEVEL | OBJECTIVE POP-UP WILL NOT BE DISPLAYED | ADD INVENTORY MANAGER TO THE LEVEL UNDER 'C++CLASSES/RADIANCE/INVENTORY" ) );
		}
	}
}
