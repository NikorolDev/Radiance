// Fill out your copyright notice in the Description page of Project Settings.


#include "IsPlayerInRangeTask.h"
#include "Radiance/Enemies/Corrupter/CorrupterAIController.h"
#include "Radiance/Enemies/Corrupter/EnemyCorrupter.h"
#include "Radiance/Enemies/BlackboardKeys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UIsPlayerInRangeTask::UIsPlayerInRangeTask ( FObjectInitializer const& ObjectInitializer )
{
    NodeName = TEXT ( "Check Player Is In Attack Range" );
    //bNotifyBecomeRelevant = true;
}

// Check Distance Between player and enemy
EBTNodeResult::Type UIsPlayerInRangeTask::ExecuteTask ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory )
{
    // Get Player and Enemy Controller
    ACharacter* const player = UGameplayStatics::GetPlayerCharacter ( GetWorld ( ) , 0 );
    ACorrupterAIController* const controller = Cast<ACorrupterAIController> ( OwnerComp.GetAIOwner ( ) );

    // Get AI Pawn
    AEnemyCorrupter* const npc = Cast<AEnemyCorrupter> ( controller->GetPawn ( ) );

    // Get Character Movement Component of AI
    UCharacterMovementComponent* const CharacterMovementVeclocity = Cast<UCharacterMovementComponent> ( npc->GetCharacterMovement ( ) );

    bool result = npc->GetDistanceTo ( player ) <= m_fAttackRange;
    if ( result )
    {
        //GEngine->AddOnScreenDebugMessage ( -1 , 10.0f , FColor::Blue , FString::Printf ( TEXT ( "distance: %f" ) , npc->GetDistanceTo ( player ) ) );
        //GEngine->AddOnScreenDebugMessage ( -1 , 10.0f , FColor::Red , FString::Printf ( TEXT ( "Check: %f" ) , result ) );
    }

    if ( npc->GetDistanceTo ( player ) <= m_fAttackRange )
    {
         // Explode
        GEngine->AddOnScreenDebugMessage ( -1 , 10.0f , FColor::Red , FString::Printf ( TEXT ( "Explode:" ) ) );
        controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chExplode , true );
    }

    // Set Blackboard key chPlayerIsInAttackRange to true if the distance between them is less than the attack range
    controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chPlayerIsInAttackRange , result );
    controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chPlayerIsInAttackRange , result );

    // Finish Task with Success
    FinishLatentTask ( OwnerComp , EBTNodeResult::Succeeded );
    return EBTNodeResult::Succeeded;
}