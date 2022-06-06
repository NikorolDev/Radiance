// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionTypes.h"
#include "CorrupterAIController.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ACorrupterAIController 
// Author				: Saurya Saurav
// Editors				: 
// Classes Inherited	: AAIController
// Purpose				: AI Controller for Enemy
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ACorrupterAIController : public AAIController
{
	GENERATED_BODY ( )
	
public:

    //-----------------------------------------------------------------------------------------------------------------------------
    // Constructor name		: ANPC_AIController
    // Author				: Saurya Saurav
    // Editors				: 
    // Parameters			: FObjectInitializer
    // Notes				: Setup Behaviour Tree 
    //-----------------------------------------------------------------------------------------------------------------------------
    ACorrupterAIController ( FObjectInitializer const& object_initializer );

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

    // Sight Config
    class UAISenseConfig_Sight* m_SightConfig;

    // Perception Component
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Sight Config" )
        class UAIPerceptionComponent* m_PerceptionComponent;

    // Currently Adding it in the Root and referencing it for code
    // Sight Radius for Enemy
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Sight Config [DEPRECATED]" )
        float m_fSightRadius = 500.0f;

    // Peripheral Vision Angle Degrees
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Sight Config [DEPRECATED]" )
        float m_fPeripheralVisionAngleDegrees = 150.0f;

    // Lose Sight Radius
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Sight Config [DEPRECATED]" )
        float m_fLoseSightRadius = m_fSightRadius + m_fPeripheralVisionAngleDegrees;

    // Range last seen location
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Sight Config [DEPRECATED]" )
        float m_fAutoSuccessRangeFromLastSeenLocation = 900.0f;

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: OnSightTargetDetected
    // Author				: Saurya Saurav
    // Editors				: 
    // Parameters			: AActor, FAIStimulus
    // Purpose				: Callback for on sight target detected 
    //-----------------------------------------------------------------------------------------------------------------------------
    UFUNCTION ( )
        void OnSightTargetDetected ( AActor* actor , FAIStimulus const stimulus );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: SetupPerceptionsystem
    // Author				: Saurya Saurav
    // Editors				: 
    // Purpose				: Setup Perception System for Sight 
    //-----------------------------------------------------------------------------------------------------------------------------
    UFUNCTION ( )
        void SetupPerceptionsystem ( );

};
