// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Radiance/Doors/Door_Module.h"
#include "Door_Terminal.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ADoor_Terminal
// Author				: Kurtis Watson
// Classes Inherited	: ADoor_Module
// Purpose				: The terminal door requires a terminal to be activated in order to open it.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ADoor_Terminal : public ADoor_Module
{
	GENERATED_BODY()

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		:	ADoor_Terminal
	// Author				:	Kurtis Watson
	//-----------------------------------------------------------------------------------------------------------------------------
	ADoor_Terminal();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	TerminalActivated
	// Author				:	Kurtis Watson
	// Purpose				:	Overrides the parent class virtual function to allow for the attachment of a module to be
	//							recognised when the player interacts with a terminal.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void TerminalActivated() override;
};
