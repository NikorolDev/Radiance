// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Radiance/TriggerVolumes/TriggerVolume_Base.h"
#include "Radiance/InfluentiableThroughCycles.h"

#include "TriggerVolume_TimerStart.generated.h"

// Forward class declaration
class ALoopManager;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ATriggerVolume_Dialogue
// Author				: Nikodem Hamrol
// Editor				: Gaetano Trovato
// Classes Inherited	: ATriggerVolume_Base
// Purpose				: Trigger volume which prompt the start of a new cycle
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ATriggerVolume_TimerStart : public ATriggerVolume_Base, public IInfluentiableThroughCycles
{
	GENERATED_BODY()


protected:

	// Pointer to instance of loop manager
	ALoopManager* m_LoopManager;

public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		: ATriggerVolume_TimerStart()
	// Author				: Nikodem Hamrol
	// Editor				: Gaetano Trovato
	// Notes				: Sets the default values for private variables
	//----------------------------------------------------------------------------------------------------------------------------
	ATriggerVolume_TimerStart();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Reset
	// Author			: UE4
	// Editors			: Gaetano Trovato
	// Purpose			: Define behaviour when an actor is re-initialised 
	//-----------------------------------------------------------------------------------------------------------------------------
	void ResetForNextCycle_Implementation(const int32 CurrentCycle) override;

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
	// Editor			: Gaetano Trovato
	// Purpose			: This is the callback function needed to set "OnBeginOverlap" function in BeginPlay().
	// Parameters		: All of these parameters are predefined by Unreal Engine 4 for begin overlap event.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit ) override;


};
