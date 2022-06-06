// Fill out your copyright notice in the Description page of Project Settings.


#include "TooltipManager.h"

#include <Components/BillboardComponent.h>
#include <Animation/WidgetAnimation.h>
#include <Kismet/GameplayStatics.h>

#include "Radiance/Player/PlayerCharacter.h"
#include "Radiance/Player/PlayerHUD.h"

// Sets default values
ATooltipManager::ATooltipManager()
{
 	// Set this actor to not call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create and setup...
	// Billboard Component (m_pcTooltipManagerBillboard)
	m_pcTooltipManagerBillboard = CreateDefaultSubobject<UBillboardComponent>( TEXT( "TooltipManagerBillboard" ) );
	RootComponent = m_pcTooltipManagerBillboard;

	// Find the icon of the dialogue manager using the asset address reference in the engine.
	static ConstructorHelpers::FObjectFinder<UTexture2D> TooltipIcon(TEXT("/Game/Radiance/Icons/T_Icon_TooltipManager.T_Icon_TooltipManager"));

	// Check if the icon was found.
	if( TooltipIcon.Succeeded() )
	{
		// Set the sprite of the billboard.
		m_pcTooltipManagerBillboard->SetSprite( TooltipIcon.Object );
	}
}

void ATooltipManager::HideTooltip()
{
	// Hide the tooltip, which will play the aniamtion in reverse.
	m_pcPlayerHUD->HideTooltip();
}

void ATooltipManager::DisplayTooltip()
{
	// Setup a timer handle that will delay the hiding of the tooltip off screen, based on the duration of tooltip display.
	FTimerHandle fsTimerHandle;
	//GetWorldTimerManager().SetTimer( fsTimerHandle, this, &ATooltipManager::HideTooltip, m_fTooltipDurationTime, false );
	GetWorldTimerManager().SetTimer( fsTimerHandle, m_pcPlayerHUD, &UPlayerHUD::HideTooltip, m_fTooltipDurationTime, false );
}

void ATooltipManager::InitialiseTooltip( const FString& rsTooltipID )
{
	// Find the tootip using the passed in tooltip ID.
	FStructTooltipProperties* pfsTooltipProperties = m_Tooltips.Find( rsTooltipID );

	// Check if tooltips was found
	if( pfsTooltipProperties != nullptr )
	{
		// Add the tooltip into the array for potential queue
		m_afsQueueOfTooltips.Add( *pfsTooltipProperties );

		// Set the max number of tooltips to display
		m_iTooltipsToDisplay = m_afsQueueOfTooltips.Num();
		UE_LOG( LogTemp, Warning, TEXT( "Tooltips To Display: %d" ), m_iTooltipsToDisplay );

		// Check if the player hud reference exists.
		if( m_pcPlayerHUD == nullptr )
		{
			// Create a player character pointer to get the player HUD.
			APlayerCharacter* pcPlayer	= Cast<APlayerCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld(), 0 ) );
			m_pcPlayerHUD				= pcPlayer->GetHUD();
			UE_LOG( LogTemp, Warning, TEXT( "Created Player HUD: %s" ), *m_pcPlayerHUD->GetName() );
		}

		// Check if the tooltip is not currently displayed
		if( !m_bIsTooltipDisplayed )
		{
			// Set tooltips and tooltips is displayed so it cannot be overriden when stepping on a different tooltip trigger volume.
			SetTooltip();
			m_bIsTooltipDisplayed = true;
		}
	}
	else
	{
		// Print a message onto the screen and on the output log if the dialogue sequence could not be found.
		UE_LOG( LogTemp, Warning,
			TEXT( "NO TOOLTIP FOUND | NONE MATCHING DATA ON THE TRIGGER VOLUME OR TOOLTIP MANAGER | POTENTIAL TYPO IN THE IDS" ) );
		GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red,
			TEXT( "NO TOOLTIP FOUND | NONE MATCHING DATA ON THE TRIGGER VOLUME OR TOOLTIP MANAGER | POTENTIAL TYPO IN THE IDS" ) );
	}
}

void ATooltipManager::SetTooltip()
{
	// Check if there are more tooltips to display
	if( m_iTooltipID < m_iTooltipsToDisplay )
	{
		UE_LOG( LogTemp, Display, TEXT( "DISPLAY NEW TOOLTIP" ) );

		// Get the struct of tooltip properties that is currently needs to be displayed.
		FStructTooltipProperties* pfsTooltipProperties = &m_afsQueueOfTooltips[ m_iTooltipID ];

		// Set the duration of the tooltip for the delay.
		m_fTooltipDurationTime = pfsTooltipProperties->TooltipDuration;

		// Set the tooltip properties in the HUD.
		m_pcPlayerHUD->SetTooltipProperties( pfsTooltipProperties->TooltipText, pfsTooltipProperties->TooltipImage );

		// Increment tooltip id as there are more tooltips that are queued
		m_iTooltipID++;
	}
	else
	{
		UE_LOG( LogTemp, Display, TEXT( "CLOSE TOOLTIP" ) );

		// The tooltip is now not displayed.
		m_bIsTooltipDisplayed = false;

		// Reset the tooltip ID and empty the array to dequeue the tooltips completely.
		m_iTooltipID = 0;
		m_afsQueueOfTooltips.Empty();
	}
}

