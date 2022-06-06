// Fill out your copyright notice in the Description page of Project Settings.


#include "FallenAttackTask.h"
#include "Radiance/Enemies/Fallen/EnemyFallen.h"
#include "Radiance/Enemies/Fallen/FallenAIController.h"

UFallenAttackTask::UFallenAttackTask ( FObjectInitializer const& ObjectInitializer )
{
    NodeName = TEXT ( "Fallen Attack" );
}

// Send command to Attack the player
EBTNodeResult::Type UFallenAttackTask::ExecuteTask ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory )
{
    // Get AI Controller and Pawn
    AFallenAIController* const controller = Cast<AFallenAIController> ( OwnerComp.GetAIOwner ( ) );
    AEnemyFallen* const npc = Cast<AEnemyFallen> ( controller->GetPawn ( ) );

    // Attack Player
    npc->Attack ( );

    // Finish Task with Success
    FinishLatentTask ( OwnerComp , EBTNodeResult::Succeeded );
    return EBTNodeResult::Succeeded;
}


