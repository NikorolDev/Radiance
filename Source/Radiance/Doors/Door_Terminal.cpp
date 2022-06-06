// Fill out your copyright notice in the Description page of Project Settings.


#include "Radiance/Doors/Door_Terminal.h"
#include "Components/PointLightComponent.h"

ADoor_Terminal::ADoor_Terminal()
{

}

void ADoor_Terminal::TerminalActivated()
{
	Super::ModuleAttached();

	// Checks the module count.
	if (CheckModuleCount())
	{
		// Unlocks the door.
		m_bLocked = false;

		// If modules are required.
		if (Modules.Max() > 0)
		{
			m_Timeline.Play();
		}

		// Sets the colour of the doors light to green.
		Light->SetLightColor(FLinearColor::Green);
	}
}