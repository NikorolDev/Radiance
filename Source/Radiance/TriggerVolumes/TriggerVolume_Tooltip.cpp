// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_Tooltip.h"

#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>

#include "Radiance/Tooltips/TooltipManager.h"
#include "Radiance/Player/PlayerCharacter.h"
#include "Radiance/Player/PlayerHUD.h"

ATriggerVolume_Tooltip::ATriggerVolume_Tooltip()
	: m_bHasBeenTriggered (false)
{
}

void ATriggerVolume_Tooltip::BeginPlay()
{
	// Call the base class's begin play function, which would be the AActor's one as the TriggerVolume_Base does not have one.
	Super::BeginPlay();

	// Get the tooltip manager that is in the level.
	m_pcTooltipManager = Cast<ATooltipManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ATooltipManager::StaticClass() ) );

	//Check if the tooltip manager got accessed and is in the level.
	if( m_pcTooltipManager == nullptr )
	{
		// Log that the tooltip manager is missing.
		UE_LOG( LogTemp, Error,
			TEXT( "MISSING TOOLTIP MANAGER IN THE LEVEL | TOOLTIP WILL NOT INITIALISE | ADD TOOLTIP MANAGER TO THE LEVEL UNDER 'C++CLASSES/RADIANCE/TOOLTIPS" ) );
		GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red,
			TEXT( "MISSING TOOLTIP MANAGER IN THE LEVEL | TOOLTIP WILL NOT INITIALISE | ADD TOOLTIP MANAGER TO THE LEVEL UNDER 'C++CLASSES/RADIANCE/TOOLTIPS" ) );
	}

	// Setup an OnComponentBeginOverlap  callback functions to be called when an overlap begin  is triggered.
	m_BoxTriggerVolume->OnComponentBeginOverlap.AddDynamic( this, &ATriggerVolume_Tooltip::OnBeginOverlapTrigger );
}

void ATriggerVolume_Tooltip::OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit )
{
	// Check if the actor is not another TriggerVolume_Tooltip and if the actor contains a tag of player.
	// This will detect the player if it has that tag.
	if( (!m_bHasBeenTriggered) && ( OtherActor != this ) && OtherActor->Tags.Contains( "Player" ) )
	{
		//Check if the tooltip manager is in the level.
		if( m_pcTooltipManager != nullptr )
		{
			// Initialise the tooltip top display it or queue it if a tooltip is currently displayed.
			m_bHasBeenTriggered = true;
			m_pcTooltipManager->InitialiseTooltip( m_sTooltipID );
		}
		else
		{
			// Log that the tooltip manager is missing.
			UE_LOG( LogTemp, Error,
				TEXT( "MISSING TOOLTIP MANAGER IN THE LEVEL | FAILED TO INITIALISE TOOLTIP | ADD TOOLTIP MANAGER TO THE LEVEL UNDER 'C++CLASSES/RADIANCE/TOOLTIPS" ) );
			GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red,
				TEXT( "MISSING TOOLTIP MANAGER IN THE LEVEL | FAILED TO INITIALISE TOOLTIP | ADD TOOLTIP MANAGER TO THE LEVEL UNDER 'C++CLASSES/RADIANCE/TOOLTIPS" ) );
		}
	}
}
