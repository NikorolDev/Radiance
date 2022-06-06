// Fill out your copyright notice in the Description page of Project Settings.

#include "Lift_Terminal.h"
#include "Radiance/Doors/Door.h"

ALift_Terminal::ALift_Terminal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a static mesh component and set its properties.
	TerminalPosition = CreateDefaultSubobject<USceneComponent>("Terminal Position");
	TerminalPosition->SetupAttachment(LiftMesh);
}

void ALift_Terminal::TerminalActivated()
{
	// Check the module count to make sure the lift can be activated.
	if (CheckModuleCount())
	{
		// Unlock the lifts access.
		m_bLocked = false;

		if (bIsUp)
		{
			// Play the animation.
			m_Timeline.Reverse();
			Doors[0]->GetTimeline()->Reverse();
			bIsUp = false;
		}
		else
		{
			// Play the animation.
			m_Timeline.Play();
			Doors[1]->GetTimeline()->Reverse();
			bIsUp = true;
		}
	}
}

USceneComponent* ALift_Terminal::GetTerminalPosition()
{
	// Get the position of where the terminal is to be attached to.
	return TerminalPosition;
}

