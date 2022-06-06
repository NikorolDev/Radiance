// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FallenAIController.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AFallenAIController 
// Author				: Saurya Saurav
// Editors				: 
// Classes Inherited	: AAIController
// Purpose				: AI Controller for Enemy Fallen
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API AFallenAIController : public AAIController
{
    GENERATED_BODY ( )

public:

    //-----------------------------------------------------------------------------------------------------------------------------
    // Constructor name		: AFallenAIController
    // Author				: Saurya Saurav
    // Editors				: 
    // Parameters			: FObjectInitializer
    // Notes				: Setup Behaviour Tree 
    //-----------------------------------------------------------------------------------------------------------------------------
    AFallenAIController ( FObjectInitializer const& object_initializer );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: BeginPlay
    // Author				: UE4
    // Editors				: Saurya Saurav
    // Purpose				: Run Behaviour Tree
    //-----------------------------------------------------------------------------------------------------------------------------
    void BeginPlay ( ) override;

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: OnPossess
    // Author				: UE4
    // Editors				: Saurya Saurav
    // Parameters			: APawn
    // Purpose				: Initialize blackboard 
    //-----------------------------------------------------------------------------------------------------------------------------
    void OnPossess ( APawn* const Pawn ) override;

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: GetBlackboard
    // Author				: Saurya Saurav
    // Editors				: 
    // Purpose				: Getter for Blackboard
    //-----------------------------------------------------------------------------------------------------------------------------
    class UBlackboardComponent* GetBlackboard ( ) const;

protected:

    // Behaviour Tree
    UPROPERTY ( EditInstanceOnly , BlueprintReadWrite )
        class UBehaviorTree* m_BehaviorTree;

    // Behaviour Tree Component
    UPROPERTY ( EditInstanceOnly , BlueprintReadWrite )
        class UBehaviorTreeComponent* m_BehaviorTreeComponent;

    // Blackboard Component
    class UBlackboardComponent* m_Blackboard;
};
