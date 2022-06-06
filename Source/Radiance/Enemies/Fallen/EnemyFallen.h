// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "EnemyFallen.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AEnemyFallen
// Author				: Saurya Saurav
// Editors				: 
// Classes Inherited	: ACharacter
// Purpose				: Base Class for Enemy Fallen
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API AEnemyFallen : public ACharacter
{
    GENERATED_BODY ( )

public:

    //-----------------------------------------------------------------------------------------------------------------------------
    // Constructor name		: AEnemyFallen
    // Author				: Saurya Saurav
    // Editors				: 
    // Purpose              : Sets default values for this character's properties
    //-----------------------------------------------------------------------------------------------------------------------------
    AEnemyFallen ( );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: Attack
    // Author				: Saurya Saurav
    // Editors				:
    // Purpose				: Blast itself and cause surrounding damage
    //-----------------------------------------------------------------------------------------------------------------------------
    UFUNCTION ( )
        void Attack ( );

protected:

    // Called when the game starts or when spawned
    virtual void BeginPlay ( ) override;

    // Blast VFX to spawn
    UPROPERTY ( EditAnywhere , BlueprintReadWrite )
        UParticleSystem* m_BlastVFX;

    // Blast SFX to play
    UPROPERTY ( EditAnywhere , BlueprintReadWrite )
        USoundBase* m_BlastSFX;

    // Radial Force Component to apply collision impact
    UPROPERTY ( VisibleDefaultsOnly , BlueprintReadWrite )
        URadialForceComponent* m_RadialForceComponent;

public:

    // Called every frame
    virtual void Tick ( float DeltaTime ) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent ( class UInputComponent* PlayerInputComponent ) override;

};
