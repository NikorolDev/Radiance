// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams ( FEnemyInstanceDiedSignature , AEnemy_Base* , enemy , bool , IsReset );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam ( FEnemyAttackOverSignature , bool , AttackOver );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam ( FEnemyTakeHitSignature , float , TakeHit );

// Corrupter States of Movement
enum EEnemyCorrupterStates
{
	Idle        UMETA ( DisplayName = "Stopped" ) ,
	Moving      UMETA ( DisplayName = "Moving" ) ,
	Attacking   UMETA ( DisplayName = "Attacking" ) ,
};

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AEnemy_Base
// Author				: Saurya Saurav
// Classes Inherited	: ACharacter
// Purpose				: Enemy Base class for all the enemies 
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API AEnemy_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_Base();

	// Enemy Death Event
	UPROPERTY ( BlueprintAssignable , BlueprintCallable )
		FEnemyInstanceDiedSignature EnemyDie;

	// Attack is over Event
	UPROPERTY ( BlueprintAssignable , BlueprintCallable )
		FEnemyAttackOverSignature IsAttackOver;

	// Damage Enemy Event
	UPROPERTY ( BlueprintAssignable , BlueprintCallable )
		FEnemyTakeHitSignature TakeHitDamage;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: InvokeAttackOver
	// Author			: Saurya Saurav
	// Parameters		: bool
	// Purpose			: Attack Sequence is over
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION ( )
		void InvokeAttackOver ( bool state );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Die
	// Author			: Saurya Saurav
	// Parameters		: bool
	// Purpose			: Enemy Die Sequence
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION ( )
		void Die ( bool IsReset );

	// Current Movement State of Enemy
	EEnemyCorrupterStates eCurrentState;

protected:

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay
	// Author			: UE4
	// Purpose			: Called when the game starts or when spawned
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

	//Initial Health of the Enemy
	UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Base Properties" ,
				meta = ( DisplayName = "Health" , ToolTip = "Health of the Enemy" ) )
		float m_fInitialHealth;

	// Current Health of the Enemy
	float m_fCurrentHealth;

public:	

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: Tick
	// Author			: UE4
	// Parameters		: float
	// Purpose			: Called every frame
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void Tick ( float DeltaTime ) override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetupPlayerInputComponent
	// Author			: UE4
	// Parameters		: UInputComponent
	// Purpose			: Called to bind functionality to input
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void SetupPlayerInputComponent ( class UInputComponent* PlayerInputComponent ) override;

};
