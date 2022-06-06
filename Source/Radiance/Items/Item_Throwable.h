// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Base.h"
#include "Item_Throwable.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AItem_Throwable
// Author				: Kurtis Watson
// Classes Inherited	: AItem_Base
// Purpose				: To allow for the player to pull items towards them and then being able to throw.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API AItem_Throwable : public AItem_Base
{
	GENERATED_BODY()

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		:	AItem_Throwable
	// Author				:	Kurtis Watson
	//-----------------------------------------------------------------------------------------------------------------------------
	AItem_Throwable();

	// Damage to apply to the enemy if a collision occurs.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwable Properties", meta = (DisplayName = "Damage on Hit"))
	float fDamage;

	// Enables/disables curvature when thrown.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwable Properties", meta = (DisplayName = "Allow Curvature"))
	bool bAllowThrowCurve;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	ItemThrown
	// Author				:	Kurtis Watson
	// Purpose				:	To move the object towards a set location.
	// Parameters			:	v3TargetPos - Position to move actor towards.
	//-----------------------------------------------------------------------------------------------------------------------------
	void ItemThrown(FVector v3TargetPos);

protected:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Initialise
	// Author				:	Kurtis Watson
	// Purpose				:	To allow for variables etc. to be initialised, specific to this class.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void Initialise() override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	TrackTarget
	// Author				:	Kurtis Watson
	// Purpose				:	To allow for the object to move towards a target.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void TrackTarget() override;

private:

};
