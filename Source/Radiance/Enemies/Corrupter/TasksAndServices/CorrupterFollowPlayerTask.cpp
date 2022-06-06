// Fill out your copyright notice in the Description page of Project Settings.


#include "CorrupterFollowPlayerTask.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Radiance/Enemies/Corrupter/CorrupterAIController.h"
#include "Radiance/Enemies/Corrupter/EnemyCorrupter.h"
#include "Radiance/Enemies/BlackboardKeys.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "DrawDebugHelpers.h"

UCorrupterFollowPlayerTask::UCorrupterFollowPlayerTask ( FObjectInitializer const& ObjectInitializer )
{
    NodeName = TEXT ( "Follow Player" );
}

// Check Where player can go amd set the blackboard
EBTNodeResult::Type UCorrupterFollowPlayerTask::ExecuteTask ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory )
{
    // Get Player and Enemy Controller
    APlayerController* const playerController = Cast<APlayerController> ( UGameplayStatics::GetPlayerController ( GetWorld ( ) , 0 ) );
    ACharacter* const playerCharacter = Cast<ACharacter> ( playerController->GetCharacter ( ) );
    ACorrupterAIController* const controller = Cast<ACorrupterAIController> ( OwnerComp.GetAIOwner ( ) );

    // Get AI Pawn
    AEnemyCorrupter* const npc = Cast<AEnemyCorrupter> ( controller->GetPawn ( ) );

    // Get Character Movement Component of AI
    UCharacterMovementComponent* const CharacterMovementVeclocity = Cast<UCharacterMovementComponent> ( npc->GetCharacterMovement ( ) );

    // Move in circle
    //X: = originX + cos ( angle ) * radius;
    //Y: = originY + sin ( angle ) * radius;

    // replace collision detection by ukismetsystem library
    // check if reachable, inside the nav mesh
    // get nav mesh path and check

    float random = UKismetMathLibrary::RandomFloatInRange ( 0 , 360 );
    float randomHeight = UKismetMathLibrary::RandomFloatInRange ( m_fMinElevationHeightZ , m_fMaxElevationHeightZ );
    FVector target = FVector ( playerCharacter->GetActorLocation ( ).X + cos ( random ) * 500 , playerCharacter->GetActorLocation ( ).Y + sin ( random ) * 500 , playerCharacter->GetActorLocation ( ).Z + randomHeight/*+ 200*/ );

    // Get allow collidable objects in the collision sphere radius
    TArray< struct FHitResult > outHits = TArray< struct FHitResult > ( );
    FCollisionShape collisionSphere = FCollisionShape::MakeSphere ( 80.0f );
    
    //Sweep to check if the location can be accessed
    bool sphereHit = GetWorld ( )->SweepMultiByChannel ( OUT outHits , target , target + FVector::UpVector * collisionSphere.GetSphereRadius ( ) , FQuat ( ) , ECollisionChannel::ECC_WorldDynamic , collisionSphere );

    //DrawDebugSphere ( GetWorld ( ) , target , 80 , 20 , FColor::Red , false , 3.2f );

    //Line trace if the player is visible
    FHitResult OutHit;
    TArray<FHitResult> FirstHitResult = TArray<FHitResult> ( );
    FVector Start = npc->GetActorLocation ( );
    Start.Z += 250.f;
    Start.X += 250.f;
    FVector ForwardVector = npc->GetActorForwardVector ( ) + Start;
    FVector End = ( playerCharacter->GetActorLocation ( ) );
    FCollisionQueryParams CollisionParams;
    bool IsHittingObstacle = false;

    bool lineHit = GetWorld ( )->LineTraceSingleByChannel ( OutHit , ForwardVector , End , ECollisionChannel::ECC_Visibility , CollisionParams );
    
    // Check if player is visible
    if ( lineHit && sphereHit )
    {
        if ( OutHit.GetActor ( )->IsA<ACharacter> ( ) )
        {
            IsHittingObstacle = true;
            //GEngine->AddOnScreenDebugMessage ( -1 , 4.f , FColor::Red , FString::Printf ( TEXT ( "WALL: %s" ) , *OutHit.GetActor ( )->GetName ( ) ) );
            //DrawDebugLine ( GetWorld ( ) , ForwardVector , End , FColor::Red , false , 1 , 0 , 5 );
        }

    }

    // If conditions macth update blackboard key
    if ( outHits.Num ( ) == 0 && ( npc->GetDistanceTo ( playerCharacter ) >= 500 || npc->GetDistanceTo ( playerCharacter ) <= 300 ) && !IsHittingObstacle )
    {
        controller->GetBlackboard ( )->SetValueAsVector ( BlackboardKeys::chTargetLocation , target );
        controller->GetBlackboard ( )->SetValueAsVector ( BlackboardKeys::chEnemyLocationAtStart , npc->GetActorLocation ( ) );
        
        // [Deprecated] 
        // Movement using velocity
        /*
        {
            // Direction Unit Vector between npc and actualLocation
            FVector direction = UKismetMathLibrary::GetDirectionUnitVector ( npc->GetActorLocation ( ) , target );
            // Caluculate actual velocity
            FVector velocity = direction * m_fCharacterMovementSpeed;
        
            // Set Velocity
            CharacterMovementVeclocity->Velocity = velocity;
        }
        */

        npc->eCurrentState = EEnemyCorrupterStates::Moving;
        //DrawDebugLine ( GetWorld ( ) , target , npc->GetActorLocation ( ) , FColor::Green , false , 20 , 0 , 5 );
    }
    else
    {
        //GEngine->AddOnScreenDebugMessage ( -1 , 3.0f , FColor::Red , FString::Printf ( TEXT ( "Obstacle" ) ) );
    }

    // Finish Task with Success
    FinishLatentTask ( OwnerComp , EBTNodeResult::Succeeded );
    return EBTNodeResult::Succeeded;
}
