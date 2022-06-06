// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CorrupterProjectile.h"
#include "Particles/ParticleSystem.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Radiance/Enemies/Enemy_Base.h"
#include "Radiance/Enemies/Corrupter/HealthBarWidget.h"
#include "EnemyCorrupter.generated.h"

class UWidgetComponent;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AEnemyCorrupter
// Author				: Saurya Saurav
// Editors				: 
// Classes Inherited	: AEnemy_Base
// Purpose				: Class for Enemy Corrupter
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API AEnemyCorrupter : public AEnemy_Base
{
    GENERATED_BODY ( )

public:

    // Sets default values for this character's properties
    AEnemyCorrupter ( const FObjectInitializer& ObjectInitializer );

    // Called every frame
    virtual void Tick ( float DeltaTime ) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent ( class UInputComponent* PlayerInputComponent ) override;

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: Init
    // Author				: Saurya Saurav
    // Editors				:
    // Purpose				: To Initlize this instance of enemy
    //-----------------------------------------------------------------------------------------------------------------------------
    UFUNCTION ( )
        void Init ( );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: Attack
    // Author				: Saurya Saurav
    // Editors				:
    // Purpose				: Spawn a Projectile
    // Note                 : Removed functionlity, keeping it for later
    //-----------------------------------------------------------------------------------------------------------------------------
    UFUNCTION ( )
        void Attack ( );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: Explode
    // Author				: Saurya Saurav
    // Editors				:
    // Purpose				: Explode on contact with player
    //-----------------------------------------------------------------------------------------------------------------------------
    UFUNCTION ( )
        void Explode ( );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: GetHealthBarPercentage
    // Author				: Saurya Saurav
    // Editors				:
    // Purpose				: Returns Current Health Percentage
    //-----------------------------------------------------------------------------------------------------------------------------
    UFUNCTION ( BlueprintPure )
        float GetHealthBarPercentage ( ) const;

    // Radial Force Component to apply collision impact
    UPROPERTY ( VisibleDefaultsOnly , BlueprintReadWrite )
        UCapsuleComponent* m_CapsuleComponent;

private:

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: OnHit
    // Author				: Saurya Saurav
    // Editors				:
    // Purpose				: Check Collisions
    //-----------------------------------------------------------------------------------------------------------------------------
    UFUNCTION ( )
        void OnHit ( UPrimitiveComponent* HitComp , AActor* OtherActor , UPrimitiveComponent* OtherComp , FVector NormalImpulse , const FHitResult& Hit );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: TakeDamage
    // Author				: Saurya Saurav
    // Editors				:
    // Purpose				: Damage sequence when enemy gets attacked
    //-----------------------------------------------------------------------------------------------------------------------------
    UFUNCTION ( )
        virtual float TakeDamage ( float DamageAmount , FDamageEvent const& DamageEvent , AController* EventInstigator , AActor* DamageCauser ) override;

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: MoveTowardsLocation
    // Author				: Saurya Saurav
    // Parameters			: FVector , FVector , float
    // Purpose				: Move Towards the loaction using Position
    //-----------------------------------------------------------------------------------------------------------------------------
    UFUNCTION ( )
        FVector MoveTowardsLocation ( FVector v3Current , FVector v3Target , float fMaxDistanceDelta );

    //-----------------------------------------------------------------------------------------------------------------------------
    // Function Name		: TakeDamage
    // Author				: Saurya Saurav
    // Parameters			: FVector , FVector , float
    // Purpose				: Move Towards the loaction using Force
    //-----------------------------------------------------------------------------------------------------------------------------
    UFUNCTION ( )
        void AddForceToMove ( FVector v3Current , FVector v3Target , float fMaxDistanceDelta );

    // Delta Time
    float m_fDeltaTime;

    // acceleration
    float m_fAcceleration;


    float AngleAxis;

protected:

    // Called when the game starts or when spawned
    virtual void BeginPlay ( ) override;

    // Movement Speed
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Corrupter Properties" ,
                meta = ( DisplayName = "Speed" , ToolTip = "Speed of the Enemy Movement" ) )
        float m_fMovementSpeed;

    // Attack Movement Speed
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Corrupter Properties" ,
                meta = ( DisplayName = "Attack Speed" , ToolTip = "Speed of the Enemy Movement, should be greater than Speed" ) )
        float m_fAttackMovementSpeed;

    // Damage Amount
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Corrupter Properties" ,
                meta = ( DisplayName = "Damage Amount" , ToolTip = "Damage Amount when enemy attacks hits the player" ) )
        float m_fDamageAmount;

    // Effective Blast Radius
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Corrupter Properties" ,
                meta = ( DisplayName = "Explosion Radius" , ToolTip = "Sphere radis to check for the Actors after explosion to apply damage" ) )
        float m_fExplosionRadius;

    // Blast VFX to spawn
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Corrupter Properties" ,
                meta = ( DisplayName = "Explode VFX" , ToolTip = "VFX for Enemy Explosion" ) )
        UParticleSystem* m_BlastVFX;

    // Blast SFX to play
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Corrupter Properties" ,
                meta = ( DisplayName = "Explode SFX" , ToolTip = "SFX for Enemy Explosion" ) )
        USoundBase* m_BlastSFX;

    // Bullet hit VFX to spawn
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Corrupter Properties" ,
                meta = ( DisplayName = "Bullet Hit VFX" , ToolTip = "VFX for Bullet Hit" ) )
        UParticleSystem* m_BulletHitVFX;

    // Bullet hit SFX to play
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Corrupter Properties" ,
                meta = ( DisplayName = "Bullet Hit SFX" , ToolTip = "VFX for Bullet Hit" ) )
        USoundBase* m_BulletHitSFX;

    // Animation Montage for Upper Body
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Projectile Attack Sequence Properties [DEPRECATED]" ,
                meta = ( DisplayName = "Upper Body Animation Montage" , ToolTip = "Monatge for Upper Body, NOTE: Not using currently" ) )
        UAnimMontage* m_UpperBodyAnimMontage;

    // Projectile to Spawn
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Projectile Attack Sequence Properties [DEPRECATED]" ,
                meta = ( DisplayName = "Projectile Instance" , ToolTip = "Projectile Instance, NOTE: Not using currently" ) )
        TSubclassOf<class ACorrupterProjectile> m_pcTProjectile;


    // Bone Name as the spawn position
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Projectile Attack Sequence Properties [DEPRECATED]" ,
                meta = ( DisplayName = "Bone Name" , ToolTip = "Bone name from where the projectile is spawned, NOTE: Not using currently" ) )
        FName   m_sBoneName = TEXT ( "hand_r" );
    
    // Offset from the Bone Location
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Projectile Attack Sequence Properties [DEPRECATED]" ,
                meta = ( DisplayName = "Spawn Location Offset" , ToolTip = "Offset from the bone location, NOTE: Not using currently" ) )
        FVector	m_vSpawnLocationOffset;
    
    // World
    class UWorld* m_World;

    // Spawn Rotation
    UPROPERTY ( )
        FRotator m_vSpawnRoatation;

    // Spawn Location
    UPROPERTY ( )
        FVector	m_vSpawnLocation;

    // Radial Force Component to apply collision impact
    UPROPERTY ( VisibleDefaultsOnly , BlueprintReadWrite )
        URadialForceComponent* m_RadialForceComponent;

    // Health Widget Component
    UPROPERTY ( VisibleAnywhere )
        UWidgetComponent* m_HealthWidgetComp;

};
