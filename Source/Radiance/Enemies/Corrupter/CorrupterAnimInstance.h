// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CorrupterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RADIANCE_API UCorrupterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UCorrupterAnimInstance ( );

	// Used to hold the owner pawn.
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Generic" )
		APawn* OwnerPawn;

	// Used to get the owner actor.
	AActor* OwningActor;

	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Generic" )
		float Speed;

	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Generic" )
		bool Attack;

	virtual void NativeUpdateAnimation ( float DeltaSeconds ) override;

private:

	void MovementSpeed ( );

};
