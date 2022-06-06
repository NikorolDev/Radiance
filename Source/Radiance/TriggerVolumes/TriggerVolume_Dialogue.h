// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Radiance/TriggerVolumes/TriggerVolume_Base.h"
#include "TriggerVolume_Dialogue.generated.h"

// Forward class declarations
class ADialogueManager;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ATriggerVolume_Dialogue
// Author				: Nikodem Hamrol
// Classes Inherited	: ATriggerVolume_Base
// Purpose				: This class is responsible of displaying the correct dialogue sequence by passing dialogue ID to the 
//						,	dialogue manager.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ATriggerVolume_Dialogue : public ATriggerVolume_Base
{
	GENERATED_BODY()

public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		: ATriggerVolume_Dialogue()
	// Author				: Nikodem Hamrol
	// Notes				: Sets the default values for private variables
	//----------------------------------------------------------------------------------------------------------------------------
	ATriggerVolume_Dialogue();

protected:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnBeginOverlapTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	//					,	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, FHitResult& Hit)
	// Author			: Nikodem Hamrol
	// Parameters		: All of these parameters are predefined by Unreal Engine 4 for begin overlap event.
	// Purpose			: This is the callback function needed to set "OnBeginOverlap" function in BeginPlay().
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit ) override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: To add the OnBeginOverlapTrigger callback function when overlapping with the box collider.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

private:
	// This will be used to check if the dialogue trigger has been triggered so it won't play the same dialogue again.
	bool m_bHasBeenTriggered;

	// The dialogue manager needed to get the dialogue sequence and display the dialgue when overalp event is triggered.
	ADialogueManager* m_pcDialogueManager;

	// The ID of the dialogue that this trigger box will display.
	UPROPERTY( Category = Dialogue, EditInstanceOnly, meta = ( DisplayName = "Dialogue ID" ) )
		FString	m_sDialogueID;
};
