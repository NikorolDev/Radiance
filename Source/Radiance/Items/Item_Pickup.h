// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Base.h"
#include "Item_Pickup.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AItem_Pickup
// Author				: Kurtis Watson
// Classes Inherited	: AItem_Base
// Purpose				: To allow for the player to pull items towards them without being able to throw.
//-----------------------------------------------------------------------------------------------------------------------------

UCLASS()
class RADIANCE_API AItem_Pickup : public AItem_Base
{
	GENERATED_BODY()

public:

protected:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: Initialise
	// Author				: Kurtis Watson
	// Purpose				: To allow for variables etc. to be initialised, specific to this class.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void Initialise() override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: TrackTarget
	// Author				: Kurtis Watson
	// Purpose				: To allow for the object to move towards a target.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void TrackTarget() override;

private:

};
