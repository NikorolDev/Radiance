// Fill out your copyright notice in the Description page of Project Settings.


#include "CorrupterAnimInstance.h"

UCorrupterAnimInstance::UCorrupterAnimInstance ( )
{
	Speed = 0.f;
	Attack = false;
}

void UCorrupterAnimInstance::NativeUpdateAnimation ( float DeltaSeconds )
{
	// Update.
	Super::NativeUpdateAnimation ( DeltaSeconds );

	// Reference owning actor of animation instance.
	OwningActor = GetOwningActor ( );

	// Animation / offset functions.
	MovementSpeed ( );
}

void UCorrupterAnimInstance::MovementSpeed ( )
{
	if ( OwningActor )
	{
		// Set the speed based on players current velocity.
		Speed = OwningActor->GetVelocity ( ).Size ( );
	}
}