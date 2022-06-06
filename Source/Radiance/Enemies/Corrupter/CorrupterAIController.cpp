// Fill out your copyright notice in the Description page of Project Settings.


#include "CorrupterAIController.h"
#include "Radiance/Enemies/BlackboardKeys.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "AIController.h"

// Setup Behaviour Tree 
ACorrupterAIController::ACorrupterAIController ( FObjectInitializer const& object_initializer )
{
    // Find Behaviour Tree and assign to the variable
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj ( TEXT ( "BehaviorTree'/Game/Radiance/Enemies/Corrupter/BT_EnemyCorrupter.BT_EnemyCorrupter'" ) );

    if ( obj.Succeeded ( ) )
    {
        m_BehaviorTree = obj.Object;
    }

    // Create Behaviour Tree Comonent and Blackboard
    m_BehaviorTreeComponent = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent> ( this , TEXT ( "BehaviorComp" ) );
    m_Blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent> ( this , TEXT ( "BlackboardComp" ) );

    // Setup Perception for sight
    //SetupPerceptionsystem ( );

}

// Run Behaviour Tree
void ACorrupterAIController::BeginPlay ( )
{
    Super::BeginPlay ( );

    m_PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic ( this , &ACorrupterAIController::OnSightTargetDetected );

    // Run Behaviour Tree
    RunBehaviorTree ( m_BehaviorTree );
    m_BehaviorTreeComponent->StartTree ( *m_BehaviorTree );
}

// Initialize blackboard 
void ACorrupterAIController::OnPossess ( APawn* const pawn )
{
    Super::OnPossess ( pawn );

    // Initialize blackboard 
    if ( m_Blackboard )
    {
        m_Blackboard->InitializeBlackboard ( *m_BehaviorTree->BlackboardAsset );
    }
}

// Getter for Blackboard
UBlackboardComponent* ACorrupterAIController::GetBlackboard ( ) const
{
    return m_Blackboard;
}

// Callback for on sight target detected
void ACorrupterAIController::OnSightTargetDetected ( AActor* actor , FAIStimulus const stimulus )
{
    // Cast to player Character and set blackboard key CanSeePlayer to true
    if ( ACharacter* const player = UGameplayStatics::GetPlayerCharacter ( GetWorld ( ) , 0 ) )
    {
        GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chCanSeePlayer , stimulus.WasSuccessfullySensed ( ) );
    }
}

// Setup Perception System for Sight
void ACorrupterAIController::SetupPerceptionsystem ( )
{
    // Create sight perception and configure it
    m_SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight> ( TEXT ( "Sight Config" ) );
    SetPerceptionComponent ( *CreateDefaultSubobject<UAIPerceptionComponent> ( TEXT ( "Perception Component" ) ) );

    // Set Parameters for sight
    m_SightConfig->SightRadius = m_fSightRadius;
    m_SightConfig->LoseSightRadius = m_fLoseSightRadius;
    m_SightConfig->PeripheralVisionAngleDegrees = m_fPeripheralVisionAngleDegrees;
    m_SightConfig->AutoSuccessRangeFromLastSeenLocation = m_fAutoSuccessRangeFromLastSeenLocation;
    m_SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    m_SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
    m_SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    m_SightConfig->SetMaxAge ( 1.0f );

    GetPerceptionComponent ( )->SetDominantSense ( *m_SightConfig->GetSenseImplementation ( ) );

    // Callback for sight perception
    GetPerceptionComponent ( )->OnTargetPerceptionUpdated.AddDynamic ( this , &ACorrupterAIController::OnSightTargetDetected );
    
    GetPerceptionComponent ( )->ConfigureSense ( *m_SightConfig );
}