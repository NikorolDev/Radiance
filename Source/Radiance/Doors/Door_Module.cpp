// Fill out your copyright notice in the Description page of Project Settings.

#include "Door_Module.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Radiance/Player/PlayerCharacter.h"
#include "Radiance/Doors/Door_Terminal.h"
#include "Radiance/Puzzle/Slot.h"
#include "Components/PointLightComponent.h"

// Sets default values
ADoor_Module::ADoor_Module()
{

}

void ADoor_Module::ModuleAttached()
{
	Super::ModuleAttached();

	// Checks if the door is not a terminal as well as the module count.
	if (!this->IsA<ADoor_Terminal>() && CheckModuleCount())
	{
		// Unlocks the door.
		m_bLocked = false;

		// Plays the open animation.
		m_Timeline.Play();

		// Sets the colour of the doors light to green.
		Light->SetLightColor(FLinearColor::Green);
	}
}
