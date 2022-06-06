// Fill out your copyright notice in the Description page of Project Settings.

#include "FallenPlayerIsInRangeService.h"
#include "Radiance/Enemies/Fallen/FallenAIController.h"
#include "Radiance/Enemies/Fallen/EnemyFallen.h"
#include "Radiance/Enemies/BlackboardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UFallenPlayerIsInRangeService::UFallenPlayerIsInRangeService ( )
{
    NodeName = TEXT ( "Check Range" );
    bNotifyBecomeRelevant = true;
}

// Check if the distance between Player and Enemy entity is in Attack Range 
void UFallenPlayerIsInRangeService::OnBecomeRelevant ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory )
{
    Super::OnBecomeRelevant ( OwnerComp , NodeMemory );

    // Get AI Controller and Enemy Pawn
    AFallenAIController* const controller = Cast<AFallenAIController> ( OwnerComp.GetAIOwner ( ) );
    AEnemyFallen* const npc = Cast<AEnemyFallen> ( controller->GetPawn ( ) );

    // Get Player Character
    ACharacter* const player = UGameplayStatics::GetPlayerCharacter ( GetWorld ( ) , 0 );
    float distanceToPlayer = npc->GetDistanceTo ( player );
    
    // Set Blackboard key chPlayerIsInAttackRange to true if the distance between them is less than the attack range
    controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chPlayerIsInAttackRange , distanceToPlayer <= m_fRange );
    
}