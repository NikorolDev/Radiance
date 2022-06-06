// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateTowardsPlayerTask.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Radiance/Enemies/Corrupter/EnemyCorrupter.h"
#include "Radiance/Enemies/Corrupter/CorrupterAIController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "AIController.h"

URotateTowardsPlayerTask::URotateTowardsPlayerTask ( FObjectInitializer const& ObjectInitializer )
{
    NodeName = TEXT ( "Rotate Towards Player" );
}

// Rotate Towards player
EBTNodeResult::Type URotateTowardsPlayerTask::ExecuteTask ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory )
{
    // Get Player Character
    ACharacter* const player = UGameplayStatics::GetPlayerCharacter ( GetWorld ( ) , 0 );

    // Get AI Controller
    ACorrupterAIController* const controller = Cast<ACorrupterAIController> ( OwnerComp.GetAIOwner ( ) );

    // Get AI Pawn
    AEnemyCorrupter* const npc = Cast<AEnemyCorrupter> ( controller->GetPawn ( ) );

    // Set Focus to player
    controller->SetFocus ( player );

    // Finish Task with Success
    FinishLatentTask ( OwnerComp , EBTNodeResult::Succeeded );
    return EBTNodeResult::Succeeded;
}
