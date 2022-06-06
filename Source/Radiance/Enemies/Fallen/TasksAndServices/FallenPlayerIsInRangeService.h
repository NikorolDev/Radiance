// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "FallenPlayerIsInRangeService.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UFallenPlayerIsInRangeService
// Author				: Saurya Saurav
// Editors				: 
// Classes Inherited	: UBTService_BlueprintBase
// Purpose				: Service for checking if player is the range
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API UFallenPlayerIsInRangeService : public UBTService_BlueprintBase
{
	GENERATED_BODY ( )
	
public:

    //-----------------------------------------------------------------------------------------------------------------------------
    // Constructor name		: UFallenPlayerIsInRangeService
    // Author				: Saurya Saurav
    // Editors				: 
    // Notes				: Set Node Name
    //-----------------------------------------------------------------------------------------------------------------------------
    UFallenPlayerIsInRangeService ( );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: OnBecomeRelevant
    // Author				: UE4
    // Editors				: Saurya Saurav
    // Parameters			: UBehaviorTreeComponent, uint8
    // Purpose				: Check if the distance between Player and Enemy entity is in Attack Range 
    //-----------------------------------------------------------------------------------------------------------------------------
    virtual void OnBecomeRelevant ( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory ) override;

protected:

    // Range to Check for
    UPROPERTY ( EditAnywhere , BlueprintReadWrite )
        float m_fRange = 125.0f;

};
