// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CorupterGoToAttackTargetTask.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UCorupterGoToAttackTargetTask
// Author				: Saurya Saurav
// Classes Inherited	: UBTTask_BlackboardBase
// Purpose				: Task for setting up the attack location 
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API UCorupterGoToAttackTargetTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
    //-----------------------------------------------------------------------------------------------------------------------------
    // Constructor name		: UCorupterGoToAttackTargetTask
    // Author				: Saurya Saurav
    // Editors				: 
    // Parameters			: FObjectInitializer
    //-----------------------------------------------------------------------------------------------------------------------------
    UCorupterGoToAttackTargetTask ( FObjectInitializer const& ObjectInitializer );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: ExecuteTask
    // Author				: Saurya Saurav
    // Editors				:
    // Parameters			: UBehaviorTreeComponent, uint8
    // Purpose				: Set up Attack Location
    // Returns              : EBTNodeResult::Type
    //-----------------------------------------------------------------------------------------------------------------------------
    EBTNodeResult::Type ExecuteTask ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory ) override;

protected:

    // Speed
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Attack Properties [DEPRECATED]" ,
                meta = ( DisplayName = "Attack Speed" , ToolTip = "Enemy Speed when it charges to the Player" ) )
        float m_fCharacterMovementSpeed;
};
