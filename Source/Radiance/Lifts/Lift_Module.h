// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Radiance/Lifts/Lift.h"
#include "Lift_Module.generated.h"

class ASlot;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			:	ALift_Module
// Author				:	Kurtis Watson
// Inherits				:	ALift - To inherit the default lift properties.
// Purpose				:	To move the player from one floor to another when activated with a module.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ALift_Module : public ALift
{
	GENERATED_BODY()

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		:	AWeapon_Base
	// Author				:	Kurtis Watson
	//-----------------------------------------------------------------------------------------------------------------------------
	ALift_Module();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	ModuleAttached
	// Author				:	Kurtis Watson
	// Purpose				:	Called when a module has been attached to the slot referencing this lift.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void ModuleAttached() override;

};
