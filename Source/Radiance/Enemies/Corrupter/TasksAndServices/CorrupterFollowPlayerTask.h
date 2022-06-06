// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CorrupterFollowPlayerTask.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UCorrupterFollowPlayerTask
// Author				: Saurya Saurav
// Editors				: 
// Classes Inherited	: UBTTask_BlackboardBase
// Purpose				: Check Where player can go amd set the blackboard
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API UCorrupterFollowPlayerTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY ( )

public:

    //-----------------------------------------------------------------------------------------------------------------------------
    // Constructor name		: UBTTask_CorrupterFollow
    // Author				: Saurya Saurav
    // Editors				: 
    // Parameters			: FObjectInitializer
    //-----------------------------------------------------------------------------------------------------------------------------
    UCorrupterFollowPlayerTask ( FObjectInitializer const& ObjectInitializer );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: ExecuteTask
    // Author				: Saurya Saurav
    // Editors				:
    // Parameters			: UBehaviorTreeComponent, uint8
    // Purpose				: Check Where player can go amd set the blackboard
    // Returns              : EBTNodeResult::Type
    //-----------------------------------------------------------------------------------------------------------------------------
    EBTNodeResult::Type ExecuteTask ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory ) override;

protected:

    // Speed
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Movement Properties [DEPRECATED]" ,
                meta = ( DisplayName = "Movement Speed" , ToolTip = "Speed to Move around" ) )
        float m_fCharacterMovementSpeed;

    // Min Z Height to travel at
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Movement Properties" ,
                meta = ( DisplayName = "Min Elevation Z Height" , ToolTip = "Min Elevation Z Height enemy can travel to" ) )
        float m_fMinElevationHeightZ;

    // Min Z Height to travel at
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Movement Properties" ,
                meta = ( DisplayName = "Min Elevation Z Height" , ToolTip = "Min Elevation Z Height enemy can travel to" ) )
        float m_fMaxElevationHeightZ;
};
