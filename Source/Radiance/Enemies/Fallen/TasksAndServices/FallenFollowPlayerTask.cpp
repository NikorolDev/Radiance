// Fill out your copyright notice in the Description page of Project Settings.


#include "FallenFollowPlayerTask.h"
#include "Radiance/Player/PlayerCharacter.h"
#include "Radiance/Enemies/Fallen/FallenAIController.h"
#include "Radiance/Enemies/BlackboardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UFallenFollowPlayerTask::UFallenFollowPlayerTask ( FObjectInitializer const& ObjectInitializer )
{
    NodeName = TEXT ( "Follow Player" );
}

// Set the blackboard key as the Character player
EBTNodeResult::Type UFallenFollowPlayerTask::ExecuteTask ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory )
{
    // Get Player and Enemy Controller
    APlayerController* const playerController = Cast<APlayerController> ( UGameplayStatics::GetPlayerController ( GetWorld ( ) , 0 ) );
    APlayerCharacter* const playerCharacter = Cast<APlayerCharacter> ( playerController->GetCharacter ( ) );
    AFallenAIController* const controller = Cast<AFallenAIController> ( OwnerComp.GetAIOwner ( ) );

    // Set Blackboard Component value
    controller->GetBlackboard ( )->SetValueAsObject ( BlackboardKeys::chTargetActor , playerCharacter );

    // Finish Task with Success
    FinishLatentTask ( OwnerComp , EBTNodeResult::Succeeded );
    return EBTNodeResult::Succeeded;
}
