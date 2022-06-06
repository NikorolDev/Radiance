// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "ResetStateTask.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UResetStateTask
// Author				: Saurya Saurav
// Editors				: 
// Classes Inherited	: UBTTask_BlackboardBase
// Purpose				: Reset Enemy State and Blackboard keys
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API UResetStateTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

    //-----------------------------------------------------------------------------------------------------------------------------
    // Constructor name		: UResetStateTask
    // Author				: Saurya Saurav
    // Editors				: 
    // Parameters			: FObjectInitializer
    //-----------------------------------------------------------------------------------------------------------------------------
    UResetStateTask ( FObjectInitializer const& ObjectInitializer );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: ExecuteTask
    // Author				: Saurya Saurav
    // Editors				:
    // Parameters			: UBehaviorTreeComponent, uint8
    // Purpose				: Resets Enemy states and blackboard keys
    // Returns              : EBTNodeResult::Type
    //-----------------------------------------------------------------------------------------------------------------------------
    EBTNodeResult::Type ExecuteTask ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory ) override;
	
};
