// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

class APlayerCharacter;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			:	UPlayerAnimInstance
// Author				:	Kurtis Watson
// Inherits				:	UAnimInstance - Allows access to anim instance so that the animation tree specific to this class can
//							be modified.
// Purpose				:	To handle all player animations based on their current state.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class RADIANCE_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		:	UPlayerAnimInstance
	// Author				:	Kurtis Watson
	//-----------------------------------------------------------------------------------------------------------------------------
	UPlayerAnimInstance();

	// Used to hold the owner pawn.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		APawn* OwnerPawn;

	// Used to get the owner actor.
	AActor* OwningActor;

	// Holds the speed of the player.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		float Speed;

	// Determines if the player is shooting or not.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool IsShooting;

	// Determines if the player is in the gravity state.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool isGravityState;

	// Determines if the player is in the gravity state.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool isDead;

	// Determines if the player is in the gravity state.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool isFalling;

	// Determines if the player is in the gravity state.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool hasLanded;

	// Holds the 'Yaw' value.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		float Yaw;

	// Holds the 'Pitch' value.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		float Pitch;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	NativeUpdateAnimation
	// Author				:	UE4
	// Purpose				:	Used to update the player animation instance.
	// Parameters			:	DeltaTime - Calculates the time different between previous and current frame.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	// Used to store the delta time to be accessed anywhere in the class.
	float m_fDeltaTime;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	MovementSpeed
	// Author				:	Kurtis Watson
	// Purpose				:	This is used to handle the move forward/right animation.
	//-----------------------------------------------------------------------------------------------------------------------------
	void MovementSpeed();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	RotateHips
	// Author				:	Kurtis Watson
	// Purpose				:	This function is used to allow for the 'Aim Offset' to rotate correctly towards where the player
	//							is looking.
	//-----------------------------------------------------------------------------------------------------------------------------
	void RotateHips();
};
