// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Radiance/Access/Access.h"
#include "Lift.generated.h"

class ASwitch;
class ADoor;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			:	ALift
// Author				:	Kurtis Watson
// Inherits				:	AAccess - To allow for the lift to be used when conditions are met.
// Purpose				:	To move the player from one floor to another when activated.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ALift : public AAccess
{
	GENERATED_BODY()

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		:	ALift
	// Author				:	Kurtis Watson
	//-----------------------------------------------------------------------------------------------------------------------------
	ALift();

	// This is the pivot point of the lift.
	UPROPERTY(EditAnywhere, Category = "Components")
		USceneComponent* Pivot;

	// Where the slot is to be attached.
	UPROPERTY(EditAnywhere, Category = "Components")
		USceneComponent* SlotPosition;

	// The lift mesh itself.
	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* LiftMesh;

	// The lift mesh itself.
	UPROPERTY(EditAnywhere, Category = "Components")
	TArray<ASwitch*> Switches;

	UPROPERTY(EditAnywhere, Category = "Components")
	TArray<ADoor*> Doors;

	// Lift moving sound.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
		USoundWave* LiftMovingSFX;

	// Lift stop sound.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
		USoundWave* LiftStopSFX;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	EndShoot
	// Author				:	Kurtis Watson
	// Purpose				:	This will return the position of where the slot is to be attached on the lift.
	//-----------------------------------------------------------------------------------------------------------------------------
	USceneComponent* GetSlotPosition();

protected:
	bool bIsUp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	MotionHandler
	// Author				:	Kurtis Watson
	// Purpose				:	Overrides the 'Motion' class to allow for the lift to be moved.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void MotionHandler() override;

	virtual void MotionFinished() override;

	void LiftCalled(FString sMessage);

private:
};
