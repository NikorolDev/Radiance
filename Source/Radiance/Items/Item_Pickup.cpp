// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Pickup.h"

void AItem_Pickup::Initialise()
{

}

void AItem_Pickup::TrackTarget()
{
	// Check if a target is active.
	if (bHasTarget)
	{
		// Move item towards target.
		PullItem();
	}
}
