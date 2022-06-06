// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item_Base.generated.h"

// Gravity states.
enum ItemState {
	Default,
	Held
};

class APlayerCharacter;
class USphereComponent;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AItem_Base
// Author				: Kurtis Watson
// Classes Inherited	: AActor
// Purpose				: To allow for the player to pull items towards their position.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API AItem_Base : public AActor
{
	GENERATED_BODY()

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		:	AItem_Base
	// Author				:	Kurtis Watson
	//-----------------------------------------------------------------------------------------------------------------------------
	AItem_Base();

	// The box trigger volume used to detect when player overlaps with it.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (DisplayName = "Sphere Collider"))
		USphereComponent* Collider;

	// This tag is used to identify the type of item.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta = (DisplayName = "Item Tag"))
		FString Tag;

	// Bool to allow lifting of an object.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Item Held"))
		bool bItemHeld;

	// Bool to allow lifting of an object.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lift Properties", meta = (DisplayName = "Lift Item"))
		bool bLiftItem = true;

	// How long the lift should be before the item is pulled.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lift Properties", meta = (DisplayName = "Lift Duration"))
		float fLiftDuration = 0.7f;

	// The speed of the lift.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lift Properties", meta = (DisplayName = "Lift Speed"))
		float fLiftSpeed = 300;

	// The height to lift the object.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lift Properties", meta = (DisplayName = "Lift Height"))
		float fLiftHeight = 100;

	// The speed at which to pull the item towards the player.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pull Properties", meta = (DisplayName = "Pull Speed"))
		float fPullSpeed = 500;

	// The drag of the object when picked up.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pull Properties", meta = (DisplayName = "Pull Drag"))
		float fPullDrag = 20;

	// The drag of the object when held.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Held Properties", meta = (DisplayName = "Held Drag"))
		float fHeldDrag = 12;

	// The drag of the object when held.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Held Properties", meta = (DisplayName = "Shake Force"))
		float fShakeForce = 100;

	// The speed at which the object is thrown.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw Properties", meta = (DisplayName = "Throw Speed"))
		float fThrowSpeed = 5000;

	// The mesh of the item.
	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* Mesh;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Tick
	// Author				:	UE4
	// Purpose				:	To allow for variables etc. to be initialised, specific to this class.
	// Parameters			:	DeltaTime - Calculates the time different between previous and current frame.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void Tick(float DeltaTime) override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	LiftItem
	// Author				:	Kurtis Watson
	// Purpose				:	To allow for the player to lift an object.
	//-----------------------------------------------------------------------------------------------------------------------------
	void LiftItem();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	SetTarget
	// Author				:	Kurtis Watson
	// Purpose				:	To allow for variables etc. to be initialised, specific to this class.
	// Parameters			:	rPlayerCharacter - Used to get the players hold position.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetTarget(APlayerCharacter* rPlayerCharacter);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Held
	// Author				:	Kurtis Watson
	// Purpose				:	Called when the item is held.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Held();
	
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Shake
	// Author				:	Kurtis Watson
	// Purpose				:	This function is called when the player is holding an item to create a 'shake' type effect.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Shake();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Dropped
	// Author				:	Kurtis Watson
	// Purpose				:	Called when the item is dropped to change values.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Dropped();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	GetIsThrown
	// Author				:	Kurtis Watson
	// Purpose				:	To get the value of if the item is thrown or not.
	// Returns				:	bIsThrown
	//-----------------------------------------------------------------------------------------------------------------------------
	bool GetIsThrown();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	GetMesh
	// Author				:	Kurtis Watson
	// Purpose				:	To get the mesh of the item held.
	// Returns				:	Mesh
	//-----------------------------------------------------------------------------------------------------------------------------
	UStaticMeshComponent* GetMesh();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	GetTag
	// Author				:	Kurtis Watson
	// Purpose				:	To return the name of the item. It is used to check the item type.
	// Returns				:	Tag
	//-----------------------------------------------------------------------------------------------------------------------------
	FString GetTag();

protected:
	// Holds the current state so that the correct properties can be applied.
	ItemState m_eCurrentState;

	// Stores whether or not the lift is complete.
	bool	m_bLiftComplete;

	// Delta time used for updated.
	float fDeltaTime;

	// Check to see if a target is set.
	bool bHasTarget;

	// Check for if the item is thrown or not.
	bool bThrown;

	// Stores the position of the target.
	FVector Target;

	// Pointer to the player character.
	APlayerCharacter* m_PlayerCharacter;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	BeginPlay
	// Author				:	UE4
	// Purpose				:	Called at game begin.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: Initialise
	// Author				: Kurtis Watson
	// Purpose				: To allow for variables etc. to be initialised, specific to child class.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void Initialise();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: TrackTarget
	// Author				: Kurtis Watson
	// Purpose				: Called in Tick() to move the item towards a target.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void TrackTarget();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: PullItem
	// Author				: Kurtis Watson
	// Purpose				: To pull the item towards the players grab location.
	//-----------------------------------------------------------------------------------------------------------------------------
	void PullItem();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	MoveTowardsLocation
	// Author				:	Kurtis Watson
	// Purpose				:	To move towards a set location.
	// Paramteter			:	v3Current	- Current position of actor.
	//							v3Target	- Target position.
	//							fSpeed		- Speed to move the object.
	//-----------------------------------------------------------------------------------------------------------------------------
	FVector MoveTowardsLocation(FVector v3Current, FVector v3Target, float fSpeed);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: OnComponentHit
	// Author				: UE4
	// Purpose				: Called when this object hits another.
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		virtual void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	// Timer to handle pull limit delay.
	FTimerHandle	m_Timer;
	FTimerHandle	m_ShakeTimer;

	// Vector that holds the value of a 'Lift-To' position when interacted with by the player.
	FVector	m_v3LiftPosition;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	MapRangedClamped
	// Author				:	Kurtis Watson
	// Purpose				:	Used to reassign one range of numbers to another based on the input value.
	//-----------------------------------------------------------------------------------------------------------------------------
	float MapRangedClamped(float fValue, float fInRangeA, float fInRangeB, float fOutRangeA, float fOutRangeB);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	LiftComplete
	// Author				:	Kurtis Watson
	// Purpose				:	Called after an items lift time has been reached.
	//-----------------------------------------------------------------------------------------------------------------------------
	void LiftComplete();
};
