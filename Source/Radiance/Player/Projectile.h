// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UPointLightComponent;
class USphereComponent;
class AEnemy_Base;
class UParticleSystem;
class UParticleSystemComponent;
class APlayerCharacter;
class UNiagaraSystem;
class UNiagaraComponent;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			:	AProjectile
// Author				:	Kurtis Watson
// Inherits				:	AActor - Inherited so it is able to be placed in the world.
// Purpose				:	Projectile that will deal damage to enemies on collision.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Pivot point of the projectile.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (DisplayName = "Sphere Collider"))
		USceneComponent* Pivot;

	// The box trigger volume used to detect when player overlaps with it.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (DisplayName = "Sphere Collider"))
		USphereComponent* Collider;

	// The mesh of the weapon.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (DisplayName = "Light"))
		UPointLightComponent* Light;

	// The time between shots.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties", meta = (DisplayName = "Speed"))
		float fSpeed = 10000;

	// Template for the wind trail particle.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties", meta = (DisplayName = "Wind Particle Template"))
		UNiagaraSystem* WindTrailSystem;

	// Particle template reference for orb.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties", meta = (DisplayName = "Particles"))
	UParticleSystem* ParticleSystem;

	// Impact particle template.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties", meta = (DisplayName = "Impact Particles"))
		UParticleSystem* ImpactParticles;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	ProjectileShot
	// Author				:	Kurtis Watson
	// Purpose				:	Called when a projectile is shot.
	//-----------------------------------------------------------------------------------------------------------------------------
	void ProjectileShot(FVector v3StartPos, FVector v3TargetPos, FRotator v3Rotation);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	GetActiveState
	// Author				:	Kurtis Watson
	// Purpose				:	Returns the active state of the projectile.
	//-----------------------------------------------------------------------------------------------------------------------------
	bool GetActiveState();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	GetCanBeFired
	// Author				:	Kurtis Watson
	// Purpose				:	Returns if the projectile can be fired or not.
	//-----------------------------------------------------------------------------------------------------------------------------
	bool GetCanBeFired();

protected:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	BeginPlay
	// Author				:	UE4
	// Purpose				:	Called at game begin.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

private:
	// Reset timer for projectile.
	FTimerHandle	m_ResetTimer;

	// Holds the delta time.
	float m_fDeltaTime;

	// Position to move between.
	FVector m_v3StartPos;
	FVector m_v3TargetPos;

	// The active state of the projectile.
	bool m_bIsActive;
	bool m_bCanBeFired;

	// Particles that will appear when fired.
	UNiagaraComponent* WindTrailParticles;
	UParticleSystemComponent* OrbParticles;


	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: OnComponentHit
	// Author				: UE4
	// Purpose				: Called when this object hits another.
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
	virtual void OnComponentHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	MoveTowardsLocation
	// Author				:	Kurtis Watson
	// Purpose				:	To move towards a set location.
	// Paramteter			:	v3Current	- Current position of actor.
	//							v3Target	- Target position.
	//							fSpeed		- Speed to move the object.
	//-----------------------------------------------------------------------------------------------------------------------------
	FVector MoveTowardsLocation(FVector v3Current, FVector v3Target, float fSpeed);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Reset
	// Author				:	Kurtis Watson
	// Purpose				:	To allow the projectile to be fired again.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Reset();
};
