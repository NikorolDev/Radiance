// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatManager.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Radiance/Enemies/Corrupter/CorrupterAIController.h"
#include "Radiance/Enemies/Corrupter/EnemyCorrupter.h"
#include "Radiance/Enemies/BlackboardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy_Base.h"
#include "Radiance/TriggerVolumes/TriggerVolume_EnemySpawner.h"
#include <Radiance/Enemies/Corrupter/CorrupterFlyingComponent.h>

// Sets default values
ACombatManager::ACombatManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void ACombatManager::BeginPlay()
{
	Super::BeginPlay();

	// Store the loop manager 
	m_LoopManager = Cast<ALoopManager> ( UGameplayStatics::GetActorOfClass ( GetWorld ( ) , ALoopManager::StaticClass ( ) ) );
	
	// Subscribe to OnResetForNextCycle and call Reset when invoked
	m_LoopManager->OnResetForNextCycle.AddUObject ( this , &ACombatManager::ResetForNextCycle_Implementation );

	m_iNumberOfEnemiesSpawned = 0;
	m_iNumberOfEnemiesAlive = 0;


	// Finding and adding Enemies from the scene
	// NOTE: Not being used as the enemies are spawned, keeping it beacuse if the design changes later on
	// [Deprecated]
	TArray<AActor*> StoreEnemies;
	TSubclassOf<AEnemy_Base> classToFind;
	classToFind = AEnemy_Base::StaticClass ( );
	UGameplayStatics::GetAllActorsOfClass ( GetWorld ( ) , classToFind , StoreEnemies );
	for ( size_t i = 0; i < StoreEnemies.Num(); i++ )
	{
		AddEnemy ( Cast<AEnemyCorrupter> ( StoreEnemies [ i ] ) );
	}
}

// Called every frame
void ACombatManager::Tick(float DeltaTime)
{
	Super::Tick ( DeltaTime );

	// Return if not initialized
	if ( !m_bInit )
		return;

	// Cooldown counter
	m_fCurrentCooldownTimer -= DeltaTime;

	// Select enemy to attack based on priorities
	for ( size_t i = 0; i < m_aListOfEnemies.Num ( ); i++ )
	{
		// null checks to avoid crash
		AEnemy_Base* enemy = m_aListOfEnemies [ i ];
		if ( enemy == nullptr )
			break;

		float distance = enemy->GetDistanceTo ( m_PlayerCharacter );

		ACorrupterAIController* const controller = Cast<ACorrupterAIController> ( enemy->GetController ( ) );

		// Checking Attack distance, number of enemies, has enemy entity attacked recently, cooldown timer
		if ( controller->GetBlackboard ( )->GetValueAsBool ( BlackboardKeys::chCanSeePlayer )/*distance <= m_fEnemyAttackDistance*/ && !m_bIsSomeoneAttacking && ( m_iHasAttackedMostRecently != i || m_aListOfEnemies.Num ( ) == 1 ) && m_fCurrentCooldownTimer <= 0 )
		{
			// Reset Cooldown timer
			m_fCurrentCooldownTimer = m_fInitialCooldown;

			// Attack Sequence activated 
			m_bIsSomeoneAttacking = true;
			m_iHasAttackedMostRecently = i;
			// null check
			if ( enemy == nullptr )
				break;

			// Update blackboard key for the enemy 
			bool IsAttacking = controller->GetBlackboard ( )->GetValueAsBool ( BlackboardKeys::chIsAttacking );
			bool AttackTarget = controller->GetBlackboard ( )->GetValueAsBool ( BlackboardKeys::chAttackTarget );

			if ( !IsAttacking && !AttackTarget )
			{
				controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chAttackTarget , true );
				controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chIsAttacking , true );
				//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("ATTACK %f"), i));
			}
		}
	}
}

// To initialize the combat manager and its members
void ACombatManager::InitializeCombat ( FStructEnemyWaveInfo WaveInstance , UWorld* World , TSubclassOf<AEnemy_Base> EnemyCorrupter , UParticleSystem* SpawnVFX , USoundBase* SpawnSFX , float InitialAttackTimer )
{
	// Set variables from Wave Spawner
	m_WaveInstance = WaveInstance;
	m_pcTEnemy = EnemyCorrupter;
	m_SpawnVFX = SpawnVFX;
	m_SpawnSFX = SpawnSFX;

	// Call Spawn Enemy function
	SpawnEnemy ( );

	// Setting up the attack timer
	m_fInitialCooldown = InitialAttackTimer;
	m_fCurrentCooldownTimer = m_fInitialCooldown;

	m_bInit = true;
}

// Handles Adding Enemies
void ACombatManager::AddEnemy ( AEnemy_Base* enemy )
{
	// Increment enemy count and add it to the list
	m_aListOfEnemies.Add ( enemy );
	m_iNumberOfEnemiesSpawned++;
	m_iNumberOfEnemiesAlive++;
}

// Handles Removing Enemies
void ACombatManager::RemoveEnemy ( AEnemy_Base* enemy , bool IsReset )
{
	// Remove enemy only if the loop manager is not reseting
	if ( !IsReset )
	{
		m_aListOfEnemies.Remove ( enemy );
	}

	m_iNumberOfEnemiesAlive--;

	// compare current number of enemies to total that can spawn 
	if ( m_WaveInstance.iTotalNumberOfEnemies > m_iNumberOfEnemiesSpawned && !IsReset )
	{
		//SpawnEnemy ( );
		GetWorld ( )->GetTimerManager ( ).SetTimer ( m_TimeHandle , this , &ACombatManager::SpawnEnemy , 2.0F , false );
	}

	// Combat over condition
	else if( m_iNumberOfEnemiesAlive <= 0 )
	{
		IsCombatOver.Broadcast ( true );
	}
}

// To Spawn Enemy wave sequence
void ACombatManager::SpawnEnemy ( )
{
	// Store Player Character
	UWorld* World = GetWorld ( );
	APlayerController* const playerController = Cast<APlayerController> ( UGameplayStatics::GetPlayerController ( World , 0 ) );
	m_PlayerCharacter = Cast<APlayerCharacter> ( playerController->GetCharacter ( ) );

	// Store Spawn Area 
	TArray<bool> spawnAreasTaken;
	for ( size_t i = 0; i < m_WaveInstance.SpawnLocations.Num ( ); i++ )
	{
		spawnAreasTaken.Add ( false );
	}

	// Number of enemies to spawn
	for ( int i = 0; i < m_WaveInstance.iMaxNumberOfEnemiesAtATime; i++ )
	{
		if ( m_iNumberOfEnemiesSpawned >= m_WaveInstance.iTotalNumberOfEnemies || m_iNumberOfEnemiesAlive >= m_WaveInstance.iMaxNumberOfEnemiesAtATime )
			break;

		float largestDistance = 0.0F;
		int idToLoad = -1;

		for ( size_t j = 0; j < m_WaveInstance.SpawnLocations.Num ( ); j++ )
		{
			float distance = m_PlayerCharacter->GetDistanceTo ( m_WaveInstance.SpawnLocations [ j ] );
			if ( distance >= largestDistance && !spawnAreasTaken [ j ] && m_iLastIDSpawn != j )
			{
				largestDistance = distance;
				idToLoad = j;
			}
		}

		// Spawn SFX and VFX
		UGameplayStatics::SpawnEmitterAtLocation ( World , m_SpawnVFX , m_WaveInstance.SpawnLocations [ idToLoad ]->GetTransform ( ) );
		UGameplayStatics::PlaySoundAtLocation ( World , m_SpawnSFX , m_WaveInstance.SpawnLocations [ idToLoad ]->GetActorLocation ( ) , 1.0f , 1.0f , 0.0f );

		// Spawn Enemy
		FActorSpawnParameters actorSpawnParams;
		actorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		AEnemyCorrupter* enemy = World->SpawnActor<AEnemyCorrupter> ( m_pcTEnemy , m_WaveInstance.SpawnLocations [ idToLoad ]->GetTransform ( ) , actorSpawnParams );


		if ( enemy == nullptr )
		{
			break;
		}

		//Spawn area taken
		spawnAreasTaken [ idToLoad ] = true;
		m_iLastIDSpawn = idToLoad;

		// Subscribe to Enemy die and Attack Over
		enemy->IsAttackOver.AddDynamic ( this , &ACombatManager::AttackOver );
		enemy->EnemyDie.AddDynamic ( this , &ACombatManager::RemoveEnemy );

		// Add Enemy and Initialize
		AddEnemy ( enemy );
		enemy->Init ( );
	}

	World->GetTimerManager ( ).ClearTimer (m_TimeHandle );
}

// Callback for when the attack is over by the enemy entity
void ACombatManager::AttackOver ( bool state )
{
	m_bIsSomeoneAttacking = false;
}

// Reset when the loop manager time runs out
void ACombatManager::Reset ( )
{
	// Reset Initialization
	m_bInit = false;
	PrimaryActorTick.bCanEverTick = false;

	// Kill all enemies
	for ( AEnemy_Base* enemy : m_aListOfEnemies )
	{
		RemoveEnemy ( enemy , true );
		enemy->SetLifeSpan ( 0.2f );
	}

	// Empty the list of enemies
	m_aListOfEnemies.Empty ( );

	// Finish resetting Invoke
	OnFinishedResetting.ExecuteIfBound ( );
}

void ACombatManager::ResetForNextCycle_Implementation ( const int32 CurrentCycle )
{
	// Reset Initialization
	m_bInit = false;
	PrimaryActorTick.bCanEverTick = false;

	// Kill all enemies
	for ( AEnemy_Base* enemy : m_aListOfEnemies )
	{
		enemy->Die ( true );
		//RemoveEnemy ( enemy , true );
	}

	// Empty the list of enemies
	m_aListOfEnemies.Empty ( );

	// Finish resetting Invoke
	OnFinishedResetting.ExecuteIfBound ( );
}
