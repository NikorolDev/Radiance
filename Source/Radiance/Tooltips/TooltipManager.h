// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Radiance/TriggerVolumes/Struct_TooltipProperties.h"
#include "TooltipManager.generated.h"

// Forward class declarations
class UBillboardComponent;
class UPlayerHUD;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ATooltipManager
// Author				: Nikodem Hamrol
// Classes Inherited	: AActor
// Purpose				: This class will hold all the tooltips, display the current tooltip, as well as forming a queue of 
//						,	tooltips when the player stepped on mant tooltip trigger volumes and handle it.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ATooltipManager : public AActor
{
	GENERATED_BODY()
	
public:	
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor Name	: ATooltipManager()
	// Author			: Nikodem Hamrol
	// Notes			: Sets up the components and default values. Sets up the components and sets the icon for the manager to
	//					,	be visualised in the map editor.
	//----------------------------------------------------------------------------------------------------------------------------
	ATooltipManager();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Tick( float DeltaTime ) override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: To check if the current tooltip is displayed so it can display a single one or the queue
	//					,	for the duration specified.
	// Parameters		: DeltaTime - The elapsed time from previous tick function call
	//----------------------------------------------------------------------------------------------------------------------------
	//virtual void Tick( float DeltaTime ) override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: DisplayTooltip()
	// Author			: Nikodem Hamrol
	// Purpose			: This will setup the delay when the "move in" aniamtion of tooltip is finished. This delay will keep 
	//					,	the current tooltip displayed until the delay is done which will hide the tooltip.
	//----------------------------------------------------------------------------------------------------------------------------
	void DisplayTooltip();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: InitialiseDialogueSequence( FString& rsDialogueID )
	// Author			: Nikodem Hamrol
	// Purpose			: Initialise the tooltip, in which it will form a queue if the player triggers multiple tooltips.
	// Parameters		: rsTooltipID - The identifier for the tooltip.
	//----------------------------------------------------------------------------------------------------------------------------
	void InitialiseTooltip( const FString& rsTooltipID );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetTooltip()
	// Author			: Nikodem Hamrol
	// Purpose			: This will set the tooltip to be displayed and will call the function to set the tooltip properties 
	//					,	on the player HUD.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetTooltip();

private:
#pragma region Private Variables (not exposed to the editor)
	// This will signal the tick function that the tooltip is displayed.
	bool m_bIsTooltipDisplayed;

	// The current time that the tooltip was displayed for.
	float m_fCurrentTooltipTime;

	// The duration of current tooltip that is displayed to be used for the delay.
	float m_fTooltipDurationTime;

	// The identifier for the tooltip that is in the queue.
	int m_iTooltipID;

	// The max number of tooltips to display.
	int m_iTooltipsToDisplay;

	// The array of tooltips that will be used a queue.
	TArray<FStructTooltipProperties> m_afsQueueOfTooltips;

	// A pointer to the player hud to display the tooltips.
	UPlayerHUD* m_pcPlayerHUD;

#pragma endregion

#pragma region Private Variables (exposed to the editor)
	// This billboard will visualise the manager in the map editor.
	UPROPERTY( EditDefaultsOnly, meta = ( DisplayName = "Tooltip Manager Display" ) )
		UBillboardComponent* m_pcTooltipManagerBillboard;

	// This tooltips table will hold all the tooltips in the level.
	UPROPERTY( Category = Tooltip, EditInstanceOnly, meta = ( DisplayName = "Tooltips" ) )
		TMap<FString, FStructTooltipProperties> m_Tooltips;

#pragma endregion

#pragma region Private Functions
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: HideTooltip()
	// Author			: Nikodem Hamrol
	// Purpose			: To call the function in the player HUD to play the animation that will hide the tooltip. This is 
	//					,	necessary for the set timer function in the display tooltips.
	//----------------------------------------------------------------------------------------------------------------------------
	void HideTooltip();

#pragma endregion
};
