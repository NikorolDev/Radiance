// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Slot.generated.h"

class AItem_ThrowableModule;
class UBoxComponent;
class UPointLightComponent;
class AAccess;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			:	ASlot
// Author				:	Kurtis Watson
// Inherits				:	AActor - Inherited so it is able to be placed in the world.
// Purpose				:	Slot that activates doors and lifts.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ASlot : public AActor
{
	GENERATED_BODY()
	
public:	
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		:	ASlot
	// Author				:	Kurtis Watson
	//-----------------------------------------------------------------------------------------------------------------------------
	ASlot();

	// The mesh of the item.
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* Collider;

	// The mesh of the item.
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* Mesh;

	// Position where the gravity item will be held.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		USceneComponent* AttachPosition;

	// The mesh of the item.
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* LightBox;

	// Light used to indicate slot state.
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Components")
	UPointLightComponent* Light;

	// Reload sound.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
		USoundWave* ActiveSFX;

	// Reload sound.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
		USoundWave* InactiveSFX;

	// This is the access class that will allow for doors/lifts to be activated.
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		TArray<AAccess*> Access;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	CheckForModule
	// Author				:	Kurtis Watson
	// Purpose				:	Returns true if a module is attached to this slot, false if not.
	//-----------------------------------------------------------------------------------------------------------------------------
	bool CheckForModule();

private:
	// Timer.
	FTimerHandle	m_CooldownTimer;

	// References the module.
	AItem_ThrowableModule* m_pcModule;

	// States.
	bool m_bCanAttach;
	bool m_bHasModule;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: OnBeginOverlapTrigger
	// Author				: UE4
	// Purpose				: Called when an object collides with the trigger attached to this class.
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void OnBeginOverlapTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: OnEndOverlapTrigger
	// Author				: UE4
	// Purpose				: Called when an object leaves the trigger attached to this class.
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void OnEndOverlapTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: ResetCanAttach
	// Author				: Kurtis Watson
	// Purpose				: Allow the slot to be attached again.
	//-----------------------------------------------------------------------------------------------------------------------------
	void ResetCanAttach();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	CheckCollisionType
	// Author				:	Kurtis Watson
	// Parameters			:	AActor - Object that collided.
	//							FString - Name to check against.
	// Purpose				:	To check the collision type of the object passed through in the parameters.
	//-----------------------------------------------------------------------------------------------------------------------------
	bool CheckCollisionType(AActor* pcObject, FString Name);

public:		
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	BeginPlay
	// Author				:	UE4
	// Purpose				:	Called at game begin.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Tick
	// Author				:	UE4
	// Purpose				:	Called each frame (update).
	// Parameters			:	DeltaTime - Calculates the time different between previous and current frame.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void Tick(float DeltaTime) override;

};
