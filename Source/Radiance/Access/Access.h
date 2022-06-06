// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Radiance/Motion/Motion.h"
#include "Access.generated.h"

class ASlot;
class UBoxComponent;
class UPointLightComponent;
class AInventoryManager;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			:	AAccess
// Author				:	Kurtis Watson
// Inherits				:	AMotion - Allows access to a timeline so that when this access class is used, it allows and child
//							to overrise an animation timeline.
// Purpose				:	Allows for doors/lifts etc. in the game to be set 'Locked' and 'Unlocked'.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API AAccess : public AMotion
{
	GENERATED_BODY()

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		:	AAccess
	// Author				:	Kurtis Watson
	//-----------------------------------------------------------------------------------------------------------------------------
	AAccess();

	// Module array used for unlocking the door.
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		TArray<ASlot*> Modules;

	// The box trigger volume used to detect when player overlaps with it.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayName = "Blocker"))
		UBoxComponent* Blocker;

	// Light used to indicate access state.
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Components")
		UPointLightComponent* Light;

	// Access granted SFX.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
		USoundWave* AccessGrantedSFX;

	// Access denied SFX.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
		USoundWave* AccessDeniedSFX;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Initialise
	// Author				:	Kurtis Watson
	// Purpose				:	Returns true or false dependant on whether all modules in the 'Modules' array are active.
	//-----------------------------------------------------------------------------------------------------------------------------
	bool CheckModuleCount();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	ModuleAttached
	// Author				:	Kurtis Watson
	// Purpose				:	Virtual so that it can be access across all child classes. This function is called when a module
	//							has been attached to any module within the array.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void ModuleAttached();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	ModuleDetached
	// Author				:	Kurtis Watson
	// Purpose				:	Virtual so that it can be access across all child classes. This function is called when a module
	//							has been detached from any module within the array.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void ModuleDetached();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	TerminalActivated
	// Author				:	Kurtis Watson
	// Purpose				:	Virtual so that it can be access across all child classes. This is called when a terminal is
	//							interacted with by the player.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void TerminalActivated();

protected:
	// Holds the locked state.
	bool m_bLocked;

private:
	// To check if the trigger volume has been triggered already.
	bool m_bHasBeenTriggered;

	// The Inventory manager that will be used to call the function that will pop-up the "New Objective" UI element.
	AInventoryManager* m_pcInventoryManager;

	// The ID of theObjective to be displayed.
	UPROPERTY(Category = Identification, EditInstanceOnly, meta = (DisplayName = "Objective ID"))
		FName m_sObjectiveID;
	
};
