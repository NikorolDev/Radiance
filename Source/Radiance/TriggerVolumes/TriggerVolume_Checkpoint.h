// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Radiance/TriggerVolumes/TriggerVolume_Base.h"
#include "TriggerVolume_Checkpoint.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ATriggerVolume_Checkpoint
// Author				: Nikodem Hamrol
// Editor				: Michalis Stratis
// Classes Inherited	: ATriggerVolume_Base
// Purpose				: This class is responsible of 
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ATriggerVolume_Checkpoint : public ATriggerVolume_Base
{
	GENERATED_BODY()

public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		: ATriggerVolume_Checkpoint()
	// Author				: Nikodem Hamrol
	// Editor				: Michalis Stratis
	// Notes				: Sets the default values for private variables
	//----------------------------------------------------------------------------------------------------------------------------
	ATriggerVolume_Checkpoint();

	FString* m_cPercentageString;
protected:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol, Michalis Stratis
	// Purpose			: To add the OnBeginOverlapTrigger callback function when overlapping with the box collider.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnBeginOverlapTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	//					,	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, FHitResult& Hit)
	// Author			: Nikodem Hamrol
	// Editor			: Michalis Stratis
	// Parameters		: All of these parameters are predefined by Unreal Engine 4 for begin overlap event.
	// Purpose			: This is the callback function needed to set "OnBeginOverlap" function in BeginPlay().
	//----------------------------------------------------------------------------------------------------------------------------

	virtual void OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit ) override;
private:
	// This will be used to check if the dialogue trigger has been triggered so it won't play the same dialogue again.
	bool m_bHasBeenTriggered;
};
