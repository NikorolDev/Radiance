// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerVolume_Base.generated.h"

// Forward Class Declarations
class UBoxComponent;
class UStaticMeshComponent;

//----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ATriggerVolume_Base
// Author				: Nikodem Hamrol
// Classes Inherited	: AActor
// Purpose				: This class acts as a base class for all trigger volumes, which will setup all the components. Each 
//						,	child will only setup the function callback when for OnBeginOverlap.
//----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ATriggerVolume_Base : public AActor
{
	GENERATED_BODY()

public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor Name	: ATriggerVolume_Base()
	// Author			: Nikodem Hamrol
	// Notes			: Sets up the components for the child classes and default values.
	//----------------------------------------------------------------------------------------------------------------------------
	ATriggerVolume_Base();

protected:
	// The box trigger volume used to detect when player overlaps with it.
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, meta = ( DisplayName = "BoxTriggerVolume" ) )
		UBoxComponent* m_BoxTriggerVolume;

	// The static mesh component that visualises the box component.
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, meta = ( DisplayName = "VisualMesh" ) )
		UStaticMeshComponent* m_VisualMesh;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnBeginOverlapTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	//					,	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, FHitResult& Hit)
	// Author			: Nikodem Hamrol
	// Parameters		: All of these parameters are predefined by Unreal Engine 4 for begin overlap event.
	// Purpose			: This is the callback function needed to set "OnBeginOverlap" function in BeginPlay().
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		virtual void OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit ) {};

		//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnEndOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	//					,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
	// Author			: Nikodem Hamrol
	// Parameters		: All of these parameters are predefined by Unreal Engine 4 for begin overlap event.
	// Purpose			: This is the callback function needed to set "OnEndOverlap" function in BeginPlay().
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		virtual void OnEndOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex ) {};
};
