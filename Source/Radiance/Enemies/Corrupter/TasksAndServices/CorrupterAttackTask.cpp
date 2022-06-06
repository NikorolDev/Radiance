// Fill out your copyright notice in the Description page of Project Settings.


#include "CorrupterAttackTask.h"
#include "Radiance/Enemies/Corrupter/EnemyCorrupter.h"
#include "Radiance/Enemies/Corrupter/CorrupterAIController.h"
#include "Radiance/Enemies/BlackboardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"

UCorrupterAttackTask::UCorrupterAttackTask ( FObjectInitializer const& ObjectInitializer )
{
    NodeName = TEXT ( "Corrupter Attack" );
}


EBTNodeResult::Type UCorrupterAttackTask::ExecuteTask ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory )
{
    // Get AI Controller and Pawn
    ACorrupterAIController* const controller = Cast<ACorrupterAIController> ( OwnerComp.GetAIOwner ( ) );
    AEnemyCorrupter* const npc = Cast<AEnemyCorrupter> ( controller->GetPawn ( ) );

    // Attack Player
    npc->Explode( );

    controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chAttackTarget , false );
    controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chExplode , false );

    // Finish Task with Success
    FinishLatentTask ( OwnerComp , EBTNodeResult::Succeeded );
    return EBTNodeResult::Succeeded;
}
