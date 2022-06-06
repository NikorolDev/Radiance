// Fill out your copyright notice in the Description page of Project Settings.

#include "Lift_Module.h"
#include "Lift_Terminal.h"
#include "Radiance/Puzzle/Slot.h"

ALift_Module::ALift_Module()
{

}

void ALift_Module::ModuleAttached()
{
	// Checks if the lift requires a terminal as well as the module count.
	if (CheckModuleCount() && !this->IsA<ALift_Terminal>())
	{
		// Unlock the lift.
		m_bLocked = false;

		// Play the lift active animation.
		m_Timeline.Play();
	}
}
