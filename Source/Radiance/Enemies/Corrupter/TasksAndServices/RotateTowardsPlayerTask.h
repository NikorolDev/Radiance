// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "RotateTowardsPlayerTask.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: URotateTowardsPlayerTask  
// Author				: Saurya Saurav
// Editors				: 
// Classes Inherited	: UBTTaskNode
// Purpose				: Task to Rotate AI towards Player
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API URotateTowardsPlayerTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY ( )
	
public:

    //-----------------------------------------------------------------------------------------------------------------------------
    // Constructor name		: UBTTask_RotateTowardsPlayer
    // Author				: Saurya Saurav
    // Editors				: 
    // Parameters			: FObjectInitializer
    //-----------------------------------------------------------------------------------------------------------------------------
    URotateTowardsPlayerTask ( FObjectInitializer const& ObjectInitializer );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: ExecuteTask
    // Author				: Saurya Saurav
    // Editors				:
    // Parameters			: UBehaviorTreeComponent, uint8
    // Purpose				: Rotate Towards player
    // Returns              : EBTNodeResult::Type
    //-----------------------------------------------------------------------------------------------------------------------------
    EBTNodeResult::Type ExecuteTask ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory ) override;

};
