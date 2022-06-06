// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Radiance/TriggerVolumes/TriggerVolume_Base.h"
#include "TriggerVolume_Objective.generated.h"

// Forward class declaration
class AInventoryManager;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ATriggerVolume_Objective
// Author				: Nikodem Hamrol
// Classes Inherited	: ATriggerVolume_Base
// Purpose				: This class is responsible for displaying "New Objetive" pop-up without using hard coded loactions
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ATriggerVolume_Objective : public ATriggerVolume_Base
{
	GENERATED_BODY()
	
public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		: ATriggerVolume_Objective()
	// Author				: Nikodem Hamrol
	// Notes				: Sets the default values for private variables
	//----------------------------------------------------------------------------------------------------------------------------
	ATriggerVolume_Objective();

protected:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: To add the OnBeginOverlapTrigger callback function when overlapping with the box collider.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnBeginOverlapTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	//					,	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, FHitResult& Hit)
	// Author			: Nikodem Hamrol
	// Purpose			: This is the callback function needed to set "OnBeginOverlap" function in BeginPlay().
	// Parameters		: All of these parameters are predefined by Unreal Engine 4 for begin overlap event.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit ) override;

private:
	// To check if the trigger volume has been triggered already.
	bool m_bHasBeenTriggered;

	// The Inventory manager that will be used to call the function that will pop-up the "New Objective" UI element.
	AInventoryManager* m_pcInventoryManager;

	// The ID of theObjective to be displayed.
	UPROPERTY( Category = Identification, EditInstanceOnly, meta = ( DisplayName = "Objective ID" ) )
		FName m_sObjectiveID;
};
