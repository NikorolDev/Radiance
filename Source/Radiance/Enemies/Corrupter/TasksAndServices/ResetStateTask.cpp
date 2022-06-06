// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetStateTask.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Radiance/Enemies/Corrupter/CorrupterAIController.h>
#include <Radiance/Enemies/Corrupter/EnemyCorrupter.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "Radiance/Enemies/BlackboardKeys.h"

UResetStateTask::UResetStateTask ( FObjectInitializer const& ObjectInitializer )
{
    NodeName = TEXT ( "Reset State" );
}

// Resets Enemy states and blackboard keys
EBTNodeResult::Type UResetStateTask::ExecuteTask ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory )
{
    // Get AI Pawn
    ACorrupterAIController* const controller = Cast<ACorrupterAIController> ( OwnerComp.GetAIOwner ( ) );
    AEnemyCorrupter* const npc = Cast<AEnemyCorrupter> ( controller->GetPawn ( ) );

    // Reset Attack Blackboard keys
    controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chAttackTarget , false );
    controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chIsAttacking , false );

    // Set to Ideal State
    npc->eCurrentState = EEnemyCorrupterStates::Idle;

    // Broadcast Attack Sequence is over
    npc->IsAttackOver.Broadcast ( true );

    // Finish Task with Success
    FinishLatentTask ( OwnerComp , EBTNodeResult::Succeeded );
    return EBTNodeResult::Succeeded;
}
