// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Radiance/TriggerVolumes/TriggerVolume_Base.h"
#include "Radiance/Enemies/CombatManager.h"
#include "Radiance/Enemies/Struct_EnemyWaveInfo.h"
#include "Radiance/LoopManager.h"
#include "Radiance/InfluentiableThroughCycles.h"
#include "Particles/ParticleSystemComponent.h"
#include "TriggerVolume_EnemySpawner.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ATriggerVolume_EnemySpawner
// Author				: Nikodem Hamrol
// Editor				: Saurya Saurav
// Classes Inherited	: ATriggerVolume_Base
// Purpose				: This class is responsible of 
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ATriggerVolume_EnemySpawner : public ATriggerVolume_Base , public IInfluentiableThroughCycles
{
	GENERATED_BODY()

public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		: ATriggerVolume_EnemySpawner()
	// Author				: Nikodem Hamrol
	// Notes				: Sets the default values for private variables
	//----------------------------------------------------------------------------------------------------------------------------
	ATriggerVolume_EnemySpawner();

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
	// Editor			: Saurya Saurav
	// Parameters		: All of these parameters are predefined by Unreal Engine 4 for begin overlap event.
	// Purpose			: Check if the player steps on it and start the combat
	// Note				: This is the callback function needed to set "OnBeginOverlap" function in BeginPlay().
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit ) override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnBeginOverlapTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	//					,	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, FHitResult& Hit)
	// Author			: Nikodem Hamrol
	// Editor			: Saurya Saurav
	// Parameters		: All of these parameters are predefined by Unreal Engine 4 for begin overlap event.
	// Purpose			: This is the callback function needed to set "OnEndOverlap" function in BeginPlay().
	//----------------------------------------------------------------------------------------------------------------------------
 	virtual void OnEndOverlapTrigger ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor ,
									   UPrimitiveComponent* OtherComp , int32 OtherBodyIndex ) override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CombatIsOver
	// Author			: Saurya Saurav
	// Parameters		: bool
	// Purpose			: Combat Over call back
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION ( )
		void CombatIsOver ( bool IsOver );
	
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CombatIsOver
	// Author			: Saurya Saurav
	// Purpose			: Reset when time runs out
	// Note				: IInfluentiableThroughCycles overridden function
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void Reset ( ) override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CombatIsOver
	// Author			: Saurya Saurav
	// Parameters		: const int32
	// Purpose			: Reset for the next cycle of loop manager
	// Note				: IInfluentiableThroughCycles overridden function
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void ResetForNextCycle_Implementation ( const int32 CurrentCycle ) override;

	// Wave Information
	UPROPERTY ( EditInstanceOnly , BlueprintReadOnly , Category = "Enemy Spawner Properties" ,
				meta = ( DisplayName = "Enemy Wave" , ToolTip = "List of Waves of Enemies based on Loop ID" ) )
		TArray<FStructEnemyWaveInfo> m_aFSEnemyWaves;
	
	// List of Blocking Objects
	UPROPERTY ( EditInstanceOnly , BlueprintReadWrite , Category = "Enemy Spawner Properties" ,
					meta = ( DisplayName = "Shadow Barriers" , ToolTip = "List of Shadow Barriers for the Combat Zone" ) )
		TArray<AActor*> m_aAcBlockingObjects;

	// Blocking Object VFX
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Spawner Properties" ,
				meta = ( DisplayName = "Shadow Barriers VFX" , ToolTip = "VFX for Shadow Barrier" ) )
		TArray<AEmitter*> m_aAcBlockingVFX;
	
	// Enemy Corrupter Reference
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Spawner Properties" ,
				meta = ( DisplayName = "Enemy Corrupter Instance" , ToolTip = "Instance of Enemy Corrupter" ) )
		TSubclassOf<AEnemy_Base> m_pcTEnemyCorrupter;

	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Spawner Properties" ,
				meta = ( DisplayName = "Attack Cooldown" , ToolTip = "Cooldown between Enemies Attack" ) )
		float m_fInitialCooldown;

	// Enemy Spawn VFX
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Spawner Properties" ,
				meta = ( DisplayName = "Spawn VFX Instance" , ToolTip = "VFX for Enemy Spawn" ) )
		UParticleSystem* m_SpawnVFX;


	// Enemy Spawn SFX
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Spawner Properties" ,
				meta = ( DisplayName = "Spawn SFX Instance" , ToolTip = "SFX for Enemy Spawn" ) )
		USoundBase* m_SpawnSFX;

	// Enemy Spawn SFX
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Spawner Properties" ,
				meta = ( DisplayName = "Enable Spawning With Module" , ToolTip = "Enable Spawning With Module" ) )
		bool m_bContactWithModule;

private:

	// Is the combat inistialized
	bool m_bIsCombatConstructed = false;

	// WaveID to Spawn
	int WaveID = 0;

	// Instance of Combat manager, spawned when player steps on trigger
	UPROPERTY()
		ACombatManager* m_CombatManager;

	// Instance of Loop manager
	UPROPERTY ( )
		ALoopManager* m_LoopManager;

	UFUNCTION ( )
		void ConstructCombatZone ( );
};
