// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Radiance/TriggerVolumes/TriggerVolume_Base.h"
#include "TriggerVolume_Ambience.generated.h"

// Forward class declarations
class UAudioComponent;
class USoundWave;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ATriggerVolume_Ambience
// Author				: Nikodem Hamrol
// Classes Inherited	: ATriggerVolume_Base
// Purpose				: This class is responsible for playing ambient sounds when 
//----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ATriggerVolume_Ambience : public ATriggerVolume_Base
{
	GENERATED_BODY()

public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		: ATriggerVolume_Ambience()
	// Author				: Nikodem Hamrol
	// Notes				: Sets the default values for private variables
	//----------------------------------------------------------------------------------------------------------------------------
	ATriggerVolume_Ambience();

protected:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: To add the OnBeginOverlapTrigger callback function when overlapping with the box collider.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnBeginOverlapTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	//					,	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, FHitResult& Hit)
	// Author			: Nikodem Hamrol
	// Purpose			: This is the callback function needed to set "OnBeginOverlap" function in BeginPlay().
	// Parameters		: All of these parameters are predefined by Unreal Engine 4 for begin overlap event.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit ) override;
	
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnEndOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	//					,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
	// Author			: Nikodem Hamrol
	// Parameters		: All of these parameters are predefined by Unreal Engine 4 for begin overlap event.
	// Purpose			: This is the callback function needed to set "OnEndOverlap" function in BeginPlay().
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void OnEndOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex ) override;

private:
	// The fade in duration for ambient sound to play when entering the trigger volume.
	UPROPERTY( Category = Audio, EditInstanceOnly, meta = ( DisplayName = "Fade In Duration" ) )
		float m_fFadeInDuration;

	// The fade out duration for ambient sound to stop playing when exiting the trigger volume.
	UPROPERTY( Category = Audio, EditInstanceOnly, meta = ( DisplayName = "Fade Out Duration" ) )
		float m_fFadeOutDuration;

	// Audio component responsible for playing the ambient sound and fading in as the player steps into the trigger volume
	UPROPERTY( Category = Audio, EditDefaultsOnly, meta = ( DisplayName = "Audio Component" ) )
		UAudioComponent* m_pcAudioComponent;

	// The sound file that will be used for ambience.
	UPROPERTY( Category = Audio, EditInstanceOnly, meta = ( DisplayName = "Ambient Sound" ) )
		USoundWave* m_pcAmbientSound;
};
