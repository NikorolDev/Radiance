// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CorrupterAttackTask.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UCorrupterAttackTask
// Author				: Saurya Saurav
// Editors				: 
// Classes Inherited	: UBTTask_BlackboardBase
// Purpose				: Task for shooting projectile
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API UCorrupterAttackTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY ( )

public:

    //-----------------------------------------------------------------------------------------------------------------------------
    // Constructor name		: UBTTask_CorrupterProjectile
    // Author				: Saurya Saurav
    // Editors				: 
    // Parameters			: FObjectInitializer
    //-----------------------------------------------------------------------------------------------------------------------------
    UCorrupterAttackTask ( FObjectInitializer const& ObjectInitializer );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: ExecuteTask
    // Author				: Saurya Saurav
    // Editors				:
    // Parameters			: UBehaviorTreeComponent, uint8
    // Purpose				: Check Distance Between player and enemy
    // Returns              : EBTNodeResult::Type
    //-----------------------------------------------------------------------------------------------------------------------------
    EBTNodeResult::Type ExecuteTask ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory ) override;
	
};
