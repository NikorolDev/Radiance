// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "IsPlayerInRangeTask.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UIsPlayerInRangeTask
// Author				: Saurya Saurav
// Editors				: 
// Classes Inherited	: UBTTask_BlackboardBase
// Purpose				: Check the Distance between Player and Enemy
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API UIsPlayerInRangeTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY ( )
	
public:

    //-----------------------------------------------------------------------------------------------------------------------------
    // Constructor name		: UBTTask_CorrupterFollow
    // Author				: Saurya Saurav
    // Editors				: 
    // Parameters			: FObjectInitializer
    //-----------------------------------------------------------------------------------------------------------------------------
    UIsPlayerInRangeTask ( FObjectInitializer const& ObjectInitializer );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: ExecuteTask
    // Author				: Saurya Saurav
    // Editors				:
    // Parameters			: UBehaviorTreeComponent, uint8
    // Purpose				: Check Distance Between player and enemy
    // Returns              : EBTNodeResult::Type
    //-----------------------------------------------------------------------------------------------------------------------------
    EBTNodeResult::Type ExecuteTask ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory ) override;

protected:

    // Attack Range to detect player
    UPROPERTY ( EditAnywhere , BlueprintReadWrite )
        float m_fAttackRange = 25.0f;
};
