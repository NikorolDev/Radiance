// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "IsEnemyInAvoidanceRangeService.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UIsEnemyInAvoidanceRangeService
// Author				: Saurya Saurav
// Editors				: 
// Classes Inherited	: UBTService_BlueprintBase
// Purpose				: Service for checking if player is the min range
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API UIsEnemyInAvoidanceRangeService : public UBTService_BlueprintBase
{
	GENERATED_BODY()
	
public:

    //-----------------------------------------------------------------------------------------------------------------------------
    // Constructor name		: UPlayerIsInRange
    // Author				: Saurya Saurav
    // Editors				: 
    // Notes				: Set Node Name
    //-----------------------------------------------------------------------------------------------------------------------------
    UIsEnemyInAvoidanceRangeService ( );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: OnBecomeRelevant
    // Author				: UE4
    // Editors				: Saurya Saurav
    // Parameters			: UBehaviorTreeComponent, uint8
    // Purpose				:  
    //-----------------------------------------------------------------------------------------------------------------------------
    virtual void OnBecomeRelevant ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory ) override;

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: TickNode
    // Author				: UE4
    // Editors				: Saurya Saurav
    // Parameters			: UBehaviorTreeComponent, uint8, DeltaSeconds
    // Purpose				: Check if the distance between Player and Attack Range 
    //-----------------------------------------------------------------------------------------------------------------------------
    virtual void TickNode ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory , float DeltaSeconds ) override;

protected:

    // Min Range allowed
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Attack Properties" ,
                meta = ( DisplayName = "Min Attack Range" , ToolTip = "Stop insides the Attack Range" ) )
        float m_fMinAttackRange;

    // Time to wait before reset
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Attack Properties" ,
                meta = ( DisplayName = "Reset Time" , ToolTip = "Cooldown time before it resets" ) )
        float m_fTimeToResetIfFails;

    // Blast Range
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Attack Properties" ,
                meta = ( DisplayName = "Blast Distance" , ToolTip = "Distance with the Player to trigger explode" ) )
        float m_fBlastDistance;

private:
    
    // Time to wait before reset
    float m_fCurrentCooldownTimeToResetIfFails;

};
