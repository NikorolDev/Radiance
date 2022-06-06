// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lift_Module.h"
#include "Lift_Terminal.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			:	ALift_Terminal
// Author				:	Kurtis Watson
// Inherits				:	ALift_Module - To allow for the lift to be used when conditions are met (including the terminal).
// Purpose				:	To move the player from one floor to another when activated.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ALift_Terminal : public ALift_Module
{
	GENERATED_BODY()

	// Position of where the terminal is to be attached to.
	UPROPERTY(EditAnywhere, Category = "Components")
		USceneComponent* TerminalPosition;

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		:	ALift_Terminal
	// Author				:	Kurtis Watson
	//-----------------------------------------------------------------------------------------------------------------------------
	ALift_Terminal();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	TerminalActivated
	// Author				:	Kurtis Watson
	// Purpose				:	This is called from the terminal when the player interacts with it.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void TerminalActivated() override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	GetTerminalPosition
	// Author				:	Kurtis Watson
	// Purpose				:	This will return the position of where the terminal is to be attached on the lift.
	//-----------------------------------------------------------------------------------------------------------------------------
	USceneComponent* GetTerminalPosition();

protected:

};
