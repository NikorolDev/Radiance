// Fill out your copyright notice in the Description page of Project Settings.

#include "FallenAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

// Setup Behaviour Tree 
AFallenAIController::AFallenAIController ( FObjectInitializer const& object_initializer )
{
    // Find Behaviour Tree and assign to the variable
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj ( TEXT ( "BehaviorTree'/Game/Radiance/Enemies/Fallen/BT_EnemyFallen.BT_EnemyFallen'" ) );

    if ( obj.Succeeded ( ) )
    {
        m_BehaviorTree = obj.Object;
    }

    // Create Behaviour Tree Comonent and Blackboard
    m_BehaviorTreeComponent = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent> ( this , TEXT ( "BehaviorComp" ) );
    m_Blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent> ( this , TEXT ( "BlackboardComp" ) );
}

// Run Behaviour Tree
void AFallenAIController::BeginPlay ( )
{
    Super::BeginPlay ( );

    // Run Behaviour Tree
    RunBehaviorTree ( m_BehaviorTree );
    m_BehaviorTreeComponent->StartTree ( *m_BehaviorTree );
}

// Initialize blackboard 
void AFallenAIController::OnPossess ( APawn* const pawn )
{
    Super::OnPossess ( pawn );

    // Initialize blackboard 
    if ( m_Blackboard )
    {
        m_Blackboard->InitializeBlackboard ( *m_BehaviorTree->BlackboardAsset );
    }
}

// Getter for Blackboard
UBlackboardComponent* AFallenAIController::GetBlackboard ( ) const
{
    return m_Blackboard;
}