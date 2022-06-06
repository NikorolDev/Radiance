// Fill out your copyright notice in the Description page of Project Settings.


#include "IsEnemyInAvoidanceRangeService.h"
#include "Radiance/Enemies/Corrupter/EnemyCorrupter.h"
#include "Radiance/Enemies/Corrupter/CorrupterAIController.h"
#include "Radiance/Enemies/BlackboardKeys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"

// Set Node Name
UIsEnemyInAvoidanceRangeService::UIsEnemyInAvoidanceRangeService ( )
{
    bNotifyBecomeRelevant = true;
    bCallTickOnSearchStart = true;
    bNotifyOnSearch = true;
    NodeName = TEXT ( "Check Player Is In Min Range" );
}

// 
void UIsEnemyInAvoidanceRangeService::OnBecomeRelevant ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory )
{

}

// Check if the distance between Player and Attack Range 
void UIsEnemyInAvoidanceRangeService::TickNode ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory , float DeltaSeconds )
{
    Super::TickNode ( OwnerComp , NodeMemory , DeltaSeconds );

    // Reset Wait Time
    m_fCurrentCooldownTimeToResetIfFails -= 0.1F;

    // Get AI Controller and Enemy Pawn
    ACorrupterAIController* const controller = Cast<ACorrupterAIController> ( OwnerComp.GetAIOwner ( ) );
    AEnemyCorrupter* const npc = Cast<AEnemyCorrupter> ( controller->GetPawn ( ) );

    // Get Player Character
    ACharacter* const player = UGameplayStatics::GetPlayerCharacter ( GetWorld ( ) , 0 );

    // Calculate Location
    FVector attackTargetLocation = controller->GetBlackboard ( )->GetValueAsVector ( BlackboardKeys::chTargetAttackLocation );
    float distanceToPlayer = npc->GetDistanceTo ( player );
    float distanceToAttackLocation = FVector::Dist ( npc->GetActorLocation ( ) , attackTargetLocation );

    
    // Set Blackboard key chPlayerIsInAttackRange to true if the distance between them is less than the attack range
    if ( distanceToAttackLocation <= m_fMinAttackRange )
    {
        controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chIsAtAttackLocation , ( true ) );

        if ( distanceToPlayer < m_fBlastDistance )
        {
            controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chExplode , ( true ) );
            
            // Reset Wait Time
            m_fCurrentCooldownTimeToResetIfFails = m_fTimeToResetIfFails;
        }
        else if ( distanceToAttackLocation <= m_fMinAttackRange )
        {
            // Restart task from root node

            // Get Character Movement Component of AI
            UCharacterMovementComponent* const CharacterMovementVeclocity = Cast<UCharacterMovementComponent> ( npc->GetCharacterMovement ( ) );

            // Set Velocity
            CharacterMovementVeclocity->Velocity = FVector::ZeroVector;
            
            // Set Blackboard Keys
            controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chAttackTarget , false );
            controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chIsAttacking , false );

            // Reset Wait Time
            m_fCurrentCooldownTimeToResetIfFails = m_fTimeToResetIfFails;

            npc->InvokeAttackOver ( true );
        }
    }

    if ( m_fTimeToResetIfFails <= 0 )
    {
        // Get Character Movement Component of AI
        UCharacterMovementComponent* const CharacterMovementVeclocity = Cast<UCharacterMovementComponent> ( npc->GetCharacterMovement ( ) );

        // Set Velocity
        CharacterMovementVeclocity->Velocity = FVector::ZeroVector;

        // Set Blackboard Keys
        controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chAttackTarget , false );
        controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chIsAttacking , false );

        npc->eCurrentState = EEnemyCorrupterStates::Idle;

        // Reset Wait Time
        m_fCurrentCooldownTimeToResetIfFails = m_fTimeToResetIfFails;
        
        npc->InvokeAttackOver ( true );
    }

}


