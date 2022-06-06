// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_EnemySpawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Radiance/Player/PlayerCharacter.h"
#include "Radiance/Items/Item_ThrowableModule.h"

ATriggerVolume_EnemySpawner::ATriggerVolume_EnemySpawner()
{

}

// Adding Callbacks
void ATriggerVolume_EnemySpawner::BeginPlay()
{
	// Call the base class's begin play function, which would be the AActor's one as the TriggerVolume_Base does not have one.
	Super::BeginPlay();

	// Setup an OnComponentBeginOverlap callback function to be called when an overlap is triggered.
	m_BoxTriggerVolume->OnComponentBeginOverlap.AddDynamic( this, &ATriggerVolume_EnemySpawner::OnBeginOverlapTrigger );
	m_BoxTriggerVolume->OnComponentEndOverlap.AddDynamic( this, &ATriggerVolume_EnemySpawner::OnEndOverlapTrigger );

	// Store LoopManager Instance and Subscribe to ResetForNextCycle
	m_LoopManager = Cast<ALoopManager> ( UGameplayStatics::GetActorOfClass ( GetWorld ( ) , ALoopManager::StaticClass ( ) ) );
	m_LoopManager->OnResetForNextCycle.AddUObject ( this, &ATriggerVolume_EnemySpawner::ResetForNextCycle_Implementation );
	
}

// Check if the player steps on it and start the combat
void ATriggerVolume_EnemySpawner::OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit )
{
	if ( ( OtherActor != NULL ) && ( OtherActor != this ) && ( OtherComponent != NULL ) && !m_bIsCombatConstructed && m_aFSEnemyWaves [ m_aFSEnemyWaves.Num ( ) <= WaveID ? m_aFSEnemyWaves.Num ( ) - 1 : WaveID ].iTotalNumberOfEnemies !=0  )
	{
		APlayerController* const playerController = Cast<APlayerController> ( UGameplayStatics::GetPlayerController ( GetWorld ( ) , 0 ) );
		AItem_ThrowableModule* const module = Cast<AItem_ThrowableModule> ( OtherActor );
		if ( ( OtherActor != this ) )
		{
			if ( ( m_bContactWithModule && OtherActor == Cast<AItem_ThrowableModule> ( OtherActor ) ) || ( OtherActor == Cast<APlayerCharacter> ( playerController->GetCharacter ( ) ) ) )
			{
				ConstructCombatZone ( );
			}
			//else if ( OtherActor == Cast<APlayerCharacter> ( playerController->GetCharacter ( ) ) )
			//{

			//}
		}
	}
}

// Triggers when player steps out of trigger of enemy spawner
void ATriggerVolume_EnemySpawner::OnEndOverlapTrigger ( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex )
{
	if ( ( OtherActor != this ) && OtherActor->Tags.Contains ( "Player" ) )
	{
		// Player out of the trigger
	}
}

void ATriggerVolume_EnemySpawner::ConstructCombatZone ( )
{
	// Block Areas so the player cannot escape the combat zone
	for ( int i = 0; i < m_aAcBlockingObjects.Num ( ); i++ )
	{
		//m_aAcBlockingObjects [ i ]->GetComponentByClass<TSubclassOf<UParticleSystem>> ( BlockingVFX );
		//UParticleSystem* particle;
		///particle->Hidde
		if ( UPrimitiveComponent* PrimitiveComponent = m_aAcBlockingObjects [ i ]->FindComponentByClass<UPrimitiveComponent> ( ) )
		{
			//PrimitiveComponent->SetCollisionResponseToAllChannels ( ECollisionResponse::ECR_Block );
			//PrimitiveComponent->SetCollisionEnabled ( ECollisionEnabled::QueryAndPhysics );
			PrimitiveComponent->SetCollisionProfileName ( TEXT ( "ItemHeld" ) );
		}
	}
	for ( size_t j = 0; j < m_aAcBlockingVFX.Num ( ); j++ )
	{
		m_aAcBlockingVFX [ j ]->SetActorHiddenInGame ( false );
		m_aAcBlockingVFX [ j ]->Activate ( );
	}

	// Spawn Combat Manager, and subscribe to when combat is over
	m_CombatManager = GetWorld ( )->SpawnActor<ACombatManager> ( ACombatManager::StaticClass ( ) );
	m_CombatManager->IsCombatOver.AddDynamic ( this , &ATriggerVolume_EnemySpawner::CombatIsOver );

	m_bIsCombatConstructed = true;

	// Initialize the Combat			
	m_CombatManager->InitializeCombat ( m_aFSEnemyWaves [ m_aFSEnemyWaves.Num ( ) <= WaveID ? m_aFSEnemyWaves.Num ( ) - 1 : WaveID ] ,
										GetWorld ( ) , m_pcTEnemyCorrupter , m_SpawnVFX , m_SpawnSFX , m_fInitialCooldown );

}

// Combat Over call back
void ATriggerVolume_EnemySpawner::CombatIsOver ( bool IsOver )
{
	// Unblock bloacking Areas of combat zone
	for ( size_t i = 0; i < m_aAcBlockingObjects.Num ( ); i++ )
	{
		//TArray<AActor*> BlockingVFX;
		//m_aAcBlockingObjects [ i ]->GetAllChildActors ( BlockingVFX );
		if ( UPrimitiveComponent* PrimitiveComponent = m_aAcBlockingObjects [ i ]->FindComponentByClass<UPrimitiveComponent> ( ) )
		{
			PrimitiveComponent->SetCollisionResponseToAllChannels ( ECollisionResponse::ECR_Ignore );
			PrimitiveComponent->SetCollisionEnabled ( ECollisionEnabled::NoCollision );
		}

	}
	for ( size_t j = 0; j < m_aAcBlockingVFX.Num ( ); j++ )
	{
		m_aAcBlockingVFX [ j ]->Deactivate ( );
		m_aAcBlockingVFX [ j ]->SetActorHiddenInGame ( true );
	}
}

// Reset for the next cycle of loop manager
void ATriggerVolume_EnemySpawner::Reset ( )
{
	m_bIsCombatConstructed = false;
	m_CombatManager = nullptr;
	WaveID++;
	OnFinishedResetting.ExecuteIfBound ( );
}

// Reset for the next cycle of loop manager
void ATriggerVolume_EnemySpawner::ResetForNextCycle_Implementation ( const int32 CurrentCycle )
{
	m_bIsCombatConstructed = false;
	m_CombatManager = nullptr;
	WaveID++;
	OnFinishedResetting.ExecuteIfBound ( );
}
