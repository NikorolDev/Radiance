// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	Speed = 0.f;
	IsShooting = false;
	isGravityState = false;
	Yaw = 0.f;
	Pitch = 0.f;
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// Update.
	Super::NativeUpdateAnimation(DeltaSeconds);

	// Reference owning actor of animation instance.
	OwningActor = GetOwningActor();

	// Update the delta time float to make it useable anywhere in the class.
	m_fDeltaTime = DeltaSeconds;

	// Animation / offset functions.
	MovementSpeed();
	RotateHips();
}

void UPlayerAnimInstance::MovementSpeed()
{
	if (OwningActor)
	{
		// Set the speed based on players current velocity.
		Speed = OwningActor->GetVelocity().Size();
	}
}

void UPlayerAnimInstance::RotateHips()
{
	// Checks that there is an owner.
	if (OwnerPawn)
	{
		// Create a rotator of the current pitch and yaw.
		FRotator Current = UKismetMathLibrary::MakeRotator(0, Pitch, Yaw);

		// Create a delta rotation to rotate towards.
		FRotator DeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(OwnerPawn->GetControlRotation(), OwningActor->GetActorRotation());

		// Rotator to go from current state to delta rotation.
		FRotator InterpTo = UKismetMathLibrary::RInterpTo(Current, DeltaRotation, m_fDeltaTime, 15.f);

		// Clamp the value of the pitch and yaw to stop over rotation.
		float ClampPitch = UKismetMathLibrary::ClampAngle(InterpTo.Euler().Y, -90, 90);
		float ClampYaw = UKismetMathLibrary::ClampAngle(InterpTo.Euler().Z, -90, 90);

		// Set the new yaw and pitch.
		Pitch = ClampPitch;
		Yaw = ClampYaw;
	}
}

