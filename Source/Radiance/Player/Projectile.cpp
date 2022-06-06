// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Radiance/Enemies/Corrupter/CorrupterAIController.h"
#include "Radiance/Enemies/Enemy_Base.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Radiance/Player/PlayerCharacter.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a box component and set its properties.
	Pivot = CreateDefaultSubobject<USceneComponent>("Pivot");
	RootComponent = Pivot;

	Collider = CreateDefaultSubobject<USphereComponent>("Collider");
	Collider->SetupAttachment(Pivot);

	// Create the light attached to the orb and attach to the mesh.
	Light = CreateDefaultSubobject<UPointLightComponent>("Light");
	Light->SetupAttachment(Pivot);

	m_bIsActive = false;
	m_bCanBeFired = true;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	Light->SetVisibility(false);

	fSpeed = fSpeed * 100;

	// Direct the collision to the 'OnComponentHit' function.
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnComponentHit);

	OrbParticles = UGameplayStatics::SpawnEmitterAttached(ParticleSystem, Pivot, FName(), GetActorLocation(), GetActorRotation(), EAttachLocation::SnapToTarget, false, EPSCPoolMethod::None, false);

	WindTrailParticles = UNiagaraFunctionLibrary::SpawnSystemAttached(WindTrailSystem, Pivot, FName(), GetActorLocation(), GetActorRotation(), FVector(1, 1, 1), EAttachLocation::KeepWorldPosition, false, ENCPoolMethod::None, false, true);
}

void AProjectile::OnComponentHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (m_bIsActive && !OtherActor->IsA<AProjectile>() && !OtherActor->IsA<APlayerCharacter>())
	{
		// As the projectile has hit something, it now becomes inactive... ready to be called again.
		m_bIsActive = false;

		//// Check to see if the actor the projectile has collider with is an enemy.
		if (OtherActor->IsA<AEnemy_Base>())
		{
			// Reference the enemy controller.
			ACorrupterAIController* EnemyController = Cast<ACorrupterAIController>(OtherActor);

			// Damage the enemy.
			UGameplayStatics::ApplyDamage(OtherActor, 20, EnemyController, this, UDamageType::StaticClass());
		}

		OrbParticles->Deactivate();
		WindTrailParticles->Deactivate();

		Light->SetVisibility(false);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, GetActorLocation());

		// Move the position of the projectile off screen as it is in a pool.
		SetActorLocation(FVector::ZeroVector);

		GetWorldTimerManager().SetTimer(m_ResetTimer, this, &AProjectile::Reset, 3.f, false);
	}
}

void AProjectile::ProjectileShot(FVector v3StartPos, FVector v3TargetPos, FRotator v3Rotation)
{
	// Set the projectiles state to true.
	m_bIsActive = true;
	m_bCanBeFired = false;

	Light->SetVisibility(true);

	OrbParticles->Activate();
	WindTrailParticles->Activate();

	SetActorRotation(v3Rotation);

	// Set the starting position.
	SetActorLocation(v3StartPos);

	// Set the target position.
	m_v3TargetPos = v3TargetPos;
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fDeltaTime = DeltaTime;

	if (m_bIsActive)
	{
		// Move towards a set position at a constant speed.
		Pivot->SetRelativeLocation(MoveTowardsLocation(GetActorLocation(), m_v3TargetPos, fSpeed));

		// Create a vector of Target - Current position.
		//FVector v3TargetPos = m_v3TargetPos - GetActorLocation();

		// Add a constant impulse dependant on the clamped speed value.
		//Mesh->AddImpulse(v3TargetPos * DeltaTime);
	}
}

FVector AProjectile::MoveTowardsLocation(FVector v3Current, FVector v3Target, float fMaxDistanceDelta)
{
	// Get the target position.
	FVector TargetPos = v3Target - v3Current;

	// Delta to move at constant speed.
	float Delta = fMaxDistanceDelta * m_fDeltaTime;

	// Distance between two points.
	float Distance = TargetPos.Size();

	if (Distance <= Delta || Distance == 0.f)
	{
		return v3Target;
	}

	// Return the new position after applying the target position.
	return v3Current + TargetPos / Distance * Delta;
}

void AProjectile::Reset()
{
	m_bCanBeFired = true;
}

bool AProjectile::GetActiveState()
{
	return m_bIsActive;
}

bool AProjectile::GetCanBeFired()
{
	return m_bCanBeFired;
}