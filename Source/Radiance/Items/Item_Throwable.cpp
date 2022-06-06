// Fill out your copyright notice in the Description page of Project Settings.

#include "Item_Throwable.h"

AItem_Throwable::AItem_Throwable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AItem_Throwable::Initialise()
{

}

void AItem_Throwable::TrackTarget()
{
	// Check if a target is active.
	if (bHasTarget)
	{
		if (!m_bLiftComplete && bLiftItem)
		{
			// Lift the item.
			LiftItem();
		}
		else
		{
			if (bThrown)
			{
				// Move towards thrown position.
				Mesh->SetRelativeLocation(MoveTowardsLocation(GetActorLocation(), Target, fThrowSpeed));
			}
			else
			{
				// Pull the item.
				PullItem();
			}
		}
	}
}


void AItem_Throwable::ItemThrown(FVector v3TargetPos)
{
	// Set target as the item has been thrown.
	bThrown = true;

	// Reset the linear damping.
	Mesh->SetLinearDamping(0);
	Mesh->SetAngularDamping(0.01f);

	// Allow for curve after throw.
	if (!bAllowThrowCurve)
	{
		// Stop any current velocity.
		Mesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
		Mesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	}

	Target = v3TargetPos;
}