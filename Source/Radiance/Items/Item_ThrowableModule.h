// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Throwable.h"
#include "Item_ThrowableModule.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			:	AItem_ThrowableModule
// Author				:	Kurtis Watson
// Inherits				:	AItem_Throwable - Allows access to base item functionality.
// Purpose				:	Allows for the module to active doors etc.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API AItem_ThrowableModule : public AItem_Throwable
{
	GENERATED_BODY()
	
public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		:	AItem_ThrowableModule
	// Author				:	Kurtis Watson
	//-----------------------------------------------------------------------------------------------------------------------------
	AItem_ThrowableModule();

	// Sound for when gauntlet is charged.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
		USoundWave* AttachSFX;

	// Sound for when gauntlet is charged.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
		USoundWave* DetachSFX;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Attach()
	// Author				:	Kurtis Watson
	// Purpose				:	Handles the attach functionality of this object after being thrown.
	// Parameters			:	AttachPosition - Where to attach the module.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Attach(USceneComponent* AttachPosition);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Detach()
	// Author				:	Kurtis Watson
	// Purpose				:	Detach from the object if attached.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Detach();

};
