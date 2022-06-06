// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FallenFollowPlayerTask.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UFallenFollowPlayerTask
// Author				: Saurya Saurav
// Editors				: 
// Classes Inherited	: UBTTask_BlackboardBase
// Purpose				: Task to follow the player
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API UFallenFollowPlayerTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	

public:

    //-----------------------------------------------------------------------------------------------------------------------------
    // Constructor name		: UFallenFollowPlayerTask
    // Author				: Saurya Saurav
    // Editors				: 
    // Parameters			: FObjectInitializer
    //-----------------------------------------------------------------------------------------------------------------------------
    UFallenFollowPlayerTask ( FObjectInitializer const& ObjectInitializer );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: ExecuteTask
    // Author				: Saurya Saurav
    // Editors				:
    // Parameters			: UBehaviorTreeComponent, uint8
    // Purpose				: Follow the player
    // Returns              : EBTNodeResult::Type
    //-----------------------------------------------------------------------------------------------------------------------------
    EBTNodeResult::Type ExecuteTask ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory ) override;

};
