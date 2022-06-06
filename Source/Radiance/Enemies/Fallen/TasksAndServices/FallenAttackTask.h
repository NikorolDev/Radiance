// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FallenAttackTask.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UFallenAttackTask
// Author				: Saurya Saurav
// Editors				: 
// Classes Inherited	: UBTTask_BlackboardBase
// Purpose				: Task for blasting when it get's near the player
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API UFallenAttackTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY ( )
	
    //-----------------------------------------------------------------------------------------------------------------------------
    // Constructor name		: UFallenAttackTask
    // Author				: Saurya Saurav
    // Editors				: 
    // Parameters			: FObjectInitializer
    //-----------------------------------------------------------------------------------------------------------------------------
    UFallenAttackTask ( FObjectInitializer const& ObjectInitializer );
    
    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: ExecuteTask
    // Author				: Saurya Saurav
    // Editors				:
    // Parameters			: UBehaviorTreeComponent, uint8
    // Purpose				: Send command to Attack the player
    // Returns              : EBTNodeResult::Type
    //-----------------------------------------------------------------------------------------------------------------------------
    EBTNodeResult::Type ExecuteTask ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory ) override;
};
