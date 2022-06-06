// Fill out your copyright notice in the Description page of Project Settings.


#include "CanEnemyChangePositionService.h"
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
UCanEnemyChangePositionService::UCanEnemyChangePositionService ( )
{
    bNotifyBecomeRelevant = true;
    bCallTickOnSearchStart = true;
    bNotifyOnSearch = true;
    NodeName = TEXT ( "Check Player Can Change Location" );
}

// 
void UCanEnemyChangePositionService::OnBecomeRelevant ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory )
{
    //m_fTimeToResetIfFails = 8.0F;
}

// Check if the distance between Player and Attack Range 
void UCanEnemyChangePositionService::TickNode ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory , float DeltaSeconds )
{
    Super::TickNode ( OwnerComp , NodeMemory , DeltaSeconds );
    
    // Get Player and Enemy Controller
    ACharacter* const player = UGameplayStatics::GetPlayerCharacter ( GetWorld ( ) , 0 );
    ACorrupterAIController* const controller = Cast<ACorrupterAIController> ( OwnerComp.GetAIOwner ( ) );

    // Get AI Pawn
    AEnemyCorrupter* const npc = Cast<AEnemyCorrupter> ( controller->GetPawn ( ) );

    FVector target = controller->GetBlackboard ( )->GetValueAsVector ( BlackboardKeys::chTargetLocation );
    FVector initialLocation = controller->GetBlackboard ( )->GetValueAsVector ( BlackboardKeys::chEnemyLocationAtStart );
    float initDistance = FVector::Distance ( target , initialLocation );
    float distanceTravelled = FVector::Distance ( npc->GetActorLocation ( ) , initialLocation );

    float distanceToTarget = FVector::Distance ( target , npc->GetActorLocation ( ) );
    float deviationToTarget = 50;
    UCharacterMovementComponent* const CharacterMovementVeclocity = Cast<UCharacterMovementComponent> ( npc->GetCharacterMovement ( ) );
    GEngine->AddOnScreenDebugMessage ( -1 , 1.0f , FColor::Green , FString::Printf ( TEXT ( "DIST : %f" ) , distanceToTarget) );
    //if ( !IsIntInRange ( distanceToTarget , distanceToTarget - deviationToTarget , distanceToTarget + deviationToTarget ) || CharacterMovementVeclocity->Velocity.Size() <= 150  )
    //if ( IsIntInRange( distanceToTarget , initDistance - deviationToTarget , initDistance + deviationToTarget ) )
    if( distanceTravelled <= initDistance + deviationToTarget && npc->eCurrentState == EEnemyCorrupterStates::Moving )
    {
        //CharacterMovementVeclocity->Velocity = FVector::ZeroVector;
        npc->eCurrentState = EEnemyCorrupterStates::Idle;
    }


    float distance = npc->GetHorizontalDistanceTo ( player );
    // If enemy can't see player and min distance is greater than allowed
    float deviation = 50;
    if ( ( !controller->GetBlackboard ( )->GetValueAsBool ( BlackboardKeys::chCanSeePlayer ) /*|| IsIntInRange ( distance , m_fMinRange - deviation , m_fMinRange + deviation ) == false*/ )/* && npc->eCurrentState != EEnemyCorrupterStates::Moving*/ )
    {
        if ( npc->eCurrentState != EEnemyCorrupterStates::Moving )
        {
            controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chCanChangeLocation , true );

        }
        //GEngine->AddOnScreenDebugMessage ( -1 , 1.0f , FColor::Green , FString::Printf ( TEXT ( "CHANGE : %f" ) , controller->GetBlackboard ( )->GetValueAsBool ( BlackboardKeys::chCanSeePlayer ) ) );
    }
    else
    {
        GEngine->AddOnScreenDebugMessage ( -1 , 1.0f , FColor::Red , FString::Printf ( TEXT ( "DONT CHANGE" ) ) );
        controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chCanChangeLocation , false );
    }

}

// Check Is in range
bool UCanEnemyChangePositionService::IsIntInRange ( float Number , float LowerBound , float UpperBound )
{
    bool bIsMoreThanLowerBound = Number > LowerBound;
    bool bIsLessThanUpperBound = Number < UpperBound;

    return bIsMoreThanLowerBound && bIsLessThanUpperBound;
}


