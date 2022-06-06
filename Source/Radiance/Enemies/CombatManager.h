// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Corrupter/EnemyCorrupter.h"
#include "Fallen/EnemyFallen.h"
#include "Enemy_Base.h"
#include "Struct_EnemyWaveInfo.h"
#include "Radiance/Player/PlayerCharacter.h"
#include "Radiance/LoopManager.h"
#include "Radiance/InfluentiableThroughCycles.h"
#include "Components/BoxComponent.h"
#include "CombatManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FIsCombatOverSignature , bool , CombatOver );

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ACombatManager
// Author				: Saurya Saurav
// Editors				: 
// Classes Inherited	: AActor , IInfluentiableThroughCycles
// Purpose				: This class is used to handle the combat with the enemies
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ACombatManager : public AActor , public IInfluentiableThroughCycles
{
	GENERATED_BODY()
	
public:	

	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		: ACombatManager()
	// Author				: Saurya Saurav
	// Notes				: Sets default values for this actor's properties
	//----------------------------------------------------------------------------------------------------------------------------
	ACombatManager();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay() override
	// Author			: Unreal Engine 4
	// Editors			: Saurya Saurav
	// Purpose			: Called every frame
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void Tick(float DeltaTime) override;
	
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: IsCombatOver
	// Author			: Saurya Saurav
	// Editors			: 
	// Parameters		: bool
	// Purpose			: Callback for when the attack is over by the enemy entity
	//----------------------------------------------------------------------------------------------------------------------------
	UPROPERTY ( BlueprintAssignable , BlueprintCallable )
		FIsCombatOverSignature IsCombatOver;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: IsCombatOver
	// Author			: Saurya Saurav
	// Editors			: 
	// Parameters		: bool
	// Purpose			: To initialize the combat manager and its members
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION ( )
		void InitializeCombat ( FStructEnemyWaveInfo WaveInstance , UWorld* World , TSubclassOf<AEnemy_Base> EnemyCorrupter , UParticleSystem* SpawnVFX , USoundBase* SpawnSFX , float InitialAttackTimer );


protected:

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay() override
	// Author			: Unreal Engine 4
	// Editors			: Saurya Saurav
	// Purpose			: Called when the game starts or when spawned
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

	// Activate enemy attack if its inside the distance specified
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Combat Manager Properties" , 
				meta = ( DisplayName = "Enemies Attack Distance" , ToolTip = "Distnace between enemy and player to initiate attack sequence" ) )
		float m_fEnemyAttackDistance = 480.0F;

private:

	// Player Character variable
	ACharacter* m_PlayerCharacter;

	// Is any enemy entity attacking
	bool m_bIsSomeoneAttacking = false;

	// enemy entity id which attacked most recently
	int  m_iHasAttackedMostRecently = -1;

	// Intial cooldown timer and reset timer
	float m_fInitialCooldown;

	// Cooldown for attack
	float m_fCurrentCooldownTimer;

	// Is combat manage initialized
	bool m_bInit = false;

	// Total number of enemies spawned
	int  m_iNumberOfEnemiesSpawned = -1;

	// number of enemies currently alive
	int  m_iNumberOfEnemiesAlive = 0;

	// Last spawn locations ID
	int  m_iLastIDSpawn = -1;

	//UWorld* m_World;

	FTimerHandle m_TimeHandle;

	// Storing the list of enemies
	TArray<AEnemy_Base*> m_aListOfEnemies;

	// enemy to spawn
	TSubclassOf<AEnemy_Base> m_pcTEnemy;

	// enemy spawn VFX
	UParticleSystem* m_SpawnVFX;

	// enemy spawn SFX
	USoundBase* m_SpawnSFX;

	// store the instance of LoopManager
	ALoopManager* m_LoopManager;

	// Wave instance to spawn
	UPROPERTY ( )
		FStructEnemyWaveInfo m_WaveInstance;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: AddEnemy()
	// Author			: Saurya Saurav
	// Editors			: 
	// Parameters		: AEnemy_Base*
	// Purpose			: Handles Adding Enemies
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION ( )
		void AddEnemy ( AEnemy_Base* enemy );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: RemoveEnemy()
	// Author			: Saurya Saurav
	// Editors			: 
	// Parameters		: AEnemy_Base* , bool
	// Purpose			: Handles Removing Enemies
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION ( )
		void RemoveEnemy ( AEnemy_Base* enemy , bool IsReset );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SpawnEnemy
	// Author			: Saurya Saurav
	// Editors			: 
	// Purpose			: To Spawn Enemy wave sequence
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION ( )
		void SpawnEnemy ( );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: AttackOver()
	// Author			: Saurya Saurav
	// Editors			: 
	// Parameters		: bool
	// Purpose			: Callback for when the attack is over by the enemy entity
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION ( )
		void AttackOver ( bool state );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Reset
	// Author			: Saurya Saurav
	// Editors			: 
	// Purpose			: Reset when the loop manager time runs out
	// Note				: This function is implemented from IInfluentiableThroughCycles
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void Reset ( ) override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Reset
	// Author			: Saurya Saurav
	// Editors			: 
	// Purpose			: Reset when the loop manager time runs out
	// Note				: This function is implemented from IInfluentiableThroughCycles
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void ResetForNextCycle_Implementation ( const int32 CurrentCycle ) override;


};
