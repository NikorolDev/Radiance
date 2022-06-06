// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Radiance/Access/Access.h"
#include "Door.generated.h"

class UBoxComponent;
class APlayerCharacter;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ADoor
// Author				: Kurtis Watson
// Classes Inherited	: AAccess
// Purpose				: To allow for the player to pull items towards their position.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ADoor : public AAccess
{
	GENERATED_BODY()
	
public:
	ADoor();

	// The box trigger volume used to detect when player overlaps with it.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (DisplayName = "Is activated by trigger?"))
		bool IsPlayerActivated;

	// The box trigger volume used to detect when player overlaps with it.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (DisplayName = "BoxTriggerVolume"))
		UBoxComponent* Collider;

	// Left side of door.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* LeftDoorMesh;

	// Right side of door.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* RightDoorMesh;

	// Door frame mesh.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* DoorFrameMesh;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	ModuleAttached
	// Author				:	Kurtis Watson
	// Purpose				:	Called when a module is attached.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void ModuleAttached() override;

protected:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay
	// Author			: Kurtis Watson
	// Purpose			: Called at runtime begin.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: OnComponentHit
	// Author				: UE4
	// Purpose				: Called when the player overlaps the door.
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: OnComponentHit
	// Author				: UE4
	// Purpose				: Called when the player ends the overlap.
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	MotionHandler
	// Author				:	Kurtis Watson
	// Purpose				:	Allows for the motion handler to be overridden for this particular class as it may animate 
	//							differently.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void MotionHandler() override;

};
