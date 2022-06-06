// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Radiance/TriggerVolumes/TriggerVolume_Base.h"
#include "TriggerVolume_EndGame.generated.h"

//Forward class declarations
class ALevelSequenceActor;
class ULevelSequence;
class ULevelSequencePlayer;
class USplashSceneWidget;
class AMainMenuGameMode;
class ALoopManager;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ATriggerVolume_Dialogue
// Author				: Nikodem Hamrol
// Classes Inherited	: ATriggerVolume_Base
// Purpose				: This class is responsible for ending the game by stopping the functionality of certain actors and
//						,	playing the final cutscene.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ATriggerVolume_EndGame : public ATriggerVolume_Base
{
	GENERATED_BODY()
	
public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		: ATriggerVolume_EndGame()
	// Author				: Nikodem Hamrol
	// Notes				: Sets the default values for private variables
	//----------------------------------------------------------------------------------------------------------------------------
	ATriggerVolume_EndGame();

	// A pointer to the SplashSceneWidget class	(Michalis Stratis)
	USplashSceneWidget* SplashWidget;

	// A pointer to the AMainMenuGameMode class (Michalis Stratis)
	AMainMenuGameMode* MenuMode;

	// A variable of the FtimerHandle class (Michalis Stratis)  
	FTimerHandle TimerHandle;

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

	// The subclass of USplashSceneWidget that lets us include the actual widget 
	UPROPERTY( EditDefaultsOnly,BlueprintReadWrite )
		TSubclassOf<USplashSceneWidget>							m_pcSplashWidget;

private:
	// The loop manager to stop the loop when finishing the game. This to not reset the game whilst in the ending cutscene.
	ALoopManager* m_pcLoopManager;

	// The sequence player to play the final cutscene.
	ULevelSequencePlayer* m_pcLevelSequencePlayer;

	// The sequence actor that is in the level which holds the sequence to play.
	UPROPERTY( Category = Cutscene, EditInstanceOnly, meta = ( DisplayName = "Cutscene" ) )
		ALevelSequenceActor* m_pcFinalCutscene;
};
