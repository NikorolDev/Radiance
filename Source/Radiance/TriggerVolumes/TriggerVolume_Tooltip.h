// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Radiance/TriggerVolumes/TriggerVolume_Base.h"
#include "TriggerVolume_Tooltip.generated.h"

// Forward class declarations
class ATooltipManager;
class UPlayerHUD;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ATriggerVolume_Tooltip
// Author				: Nikodem Hamrol
// Classes Inherited	: ATriggerVolume_Base
// Purpose				: This class is responsible for playing ambient sounds when 
//----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ATriggerVolume_Tooltip : public ATriggerVolume_Base
{
	GENERATED_BODY()
	
public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		: ATriggerVolume_Tooltip()
	// Author				: Nikodem Hamrol
	// Notes				: Sets the default values for private variables
	//----------------------------------------------------------------------------------------------------------------------------
	ATriggerVolume_Tooltip();

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

	// The tooltip manager that will be used to call the intialiser of the tooltips.
	ATooltipManager* m_pcTooltipManager;

	// The ID of the tooltip to be displayed.
	UPROPERTY( EditInstanceOnly, meta = ( DisplayName = "Tooltip ID" ) )
		FString m_sTooltipID;
};
