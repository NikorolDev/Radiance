// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "CanEnemyChangePositionService.generated.h"

/**
 * 
 */
UCLASS()
class RADIANCE_API UCanEnemyChangePositionService : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

    //-----------------------------------------------------------------------------------------------------------------------------
    // Constructor name		: UCanEnemyChangePositionService
    // Author				: Saurya Saurav
    // Editors				: 
    // Notes				: Set Node Name
    //-----------------------------------------------------------------------------------------------------------------------------
    UCanEnemyChangePositionService ( );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: OnBecomeRelevant
    // Author				: UE4
    // Editors				: Saurya Saurav
    // Parameters			: UBehaviorTreeComponent, uint8
    // Purpose				: Check if the distance between Player and Attack Range 
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

    // Max Range allowed
    UPROPERTY ( EditAnywhere , BlueprintReadWrite )
        float m_fMinRange = 500.0f;

    UPROPERTY ( EditAnywhere , BlueprintReadWrite )
        float m_fResetTime = 8.0f;

private:

    UFUNCTION ( )
        bool IsIntInRange ( float Number , float LowerBound , float UpperBound );
	
};
