// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Radiance/Doors/Door.h"
#include "Door_Module.generated.h"

class ASlot;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ADoor_Module
// Author				: Kurtis Watson
// Classes Inherited	: ADoor
// Purpose				: The module door requires modules in order to open it.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ADoor_Module : public ADoor
{
	GENERATED_BODY()

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		:	ADoor_Module
	// Author				:	Kurtis Watson
	//-----------------------------------------------------------------------------------------------------------------------------
	ADoor_Module();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	ModuleAttached
	// Author				:	Kurtis Watson
	// Purpose				:	Overrides the parent class virtual function to allow for the attachment of a module to be handled
	//							correctly.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void ModuleAttached() override;

};
