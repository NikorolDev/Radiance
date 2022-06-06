// Fill out your copyright notice in the Description page of Project Settings.


#include "CorupterGoToAttackTargetTask.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Radiance/Enemies/Corrupter/CorrupterAIController.h"
#include "Radiance/Enemies/Corrupter/EnemyCorrupter.h"
#include "Radiance/Enemies/BlackboardKeys.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

// Set Nodes name 
UCorupterGoToAttackTargetTask::UCorupterGoToAttackTargetTask ( FObjectInitializer const& ObjectInitializer )
{
    NodeName = TEXT ( "Follow Player" );
}

// Set up Attack Location
EBTNodeResult::Type UCorupterGoToAttackTargetTask::ExecuteTask ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory )
{
    // Get Player and Enemy Controller
    ACharacter* const player = UGameplayStatics::GetPlayerCharacter ( GetWorld ( ) , 0 );
    ACorrupterAIController* const controller = Cast<ACorrupterAIController> ( OwnerComp.GetAIOwner ( ) );

    // Get AI Pawn
    AEnemyCorrupter* const npc = Cast<AEnemyCorrupter> ( controller->GetPawn ( ) );

    // Get Character Movement Component of AI
    UCharacterMovementComponent* const CharacterMovementVeclocity = Cast<UCharacterMovementComponent> ( npc->GetCharacterMovement ( ) );

    // Add Z axis elevation to the actor location
    FVector actualLocation = player->GetActorLocation ( );

    // [DEPRECATED]
    // Move to Location witn Velocity
    /*
    {
        // Direction Unit Vector between npc and actualLocation
        FVector direction = UKismetMathLibrary::GetDirectionUnitVector ( npc->GetActorLocation ( ) , actualLocation );
        // Caluculate actual velocity
        FVector velocity = direction * m_fCharacterMovementSpeed;    
        // Set Velocity 
        CharacterMovementVeclocity->Velocity = velocity;
    }
    */

    // Set Blackboard Keys
    controller->GetBlackboard ( )->SetValueAsVector ( BlackboardKeys::chTargetAttackLocation , actualLocation );
    controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chIsAttacking , false );

    npc->eCurrentState = EEnemyCorrupterStates::Attacking;

    // Finish Task with Success
    FinishLatentTask ( OwnerComp , EBTNodeResult::Succeeded );
    return EBTNodeResult::Succeeded;
}

