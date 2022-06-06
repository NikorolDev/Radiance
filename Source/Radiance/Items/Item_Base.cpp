// Fill out your copyright notice in the Description page of Project Settings.

#include "Item_Base.h"
#include "Radiance/Player/PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Components/SphereComponent.h"

// Sets default values
AItem_Base::AItem_Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Create a static mesh component and set its properties.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	Mesh->SetEnableGravity(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCustomDepthStencilValue(1);
	RootComponent = Mesh;

	// Create a box component and set its properties.
	Collider = CreateDefaultSubobject<USphereComponent>("Collider");
	Collider->SetGenerateOverlapEvents(false);
	Collider->CanCharacterStepUpOn = ECB_No;
	Collider->SetCollisionProfileName("ItemDefault");
	Collider->SetupAttachment(Mesh);

	// Set the state of the item correctly.
	bThrown = false;
	bHasTarget = false;
	m_bLiftComplete = false;
}

// Called when the game starts or when spawned
void AItem_Base::BeginPlay()
{
	Super::BeginPlay();

	// Reference the function to call on collision.
	Mesh->OnComponentHit.AddDynamic(this, &AItem_Base::OnComponentHit);

	// Hide the render outline.
	Mesh->SetRenderCustomDepth(false);

	// Called to initialise any unique variables specific to an item.
	Initialise();
}

void AItem_Base::Initialise()
{
	
}

// Called every frame
void AItem_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Holds delta time so it can be accessed in the class.
	fDeltaTime = DeltaTime;

	//Function to handle lifting, pulling and throwing.
	TrackTarget();
}

void AItem_Base::SetTarget(APlayerCharacter* rPlayerCharacter)
{
	// Change state to held.
	m_eCurrentState = ItemState::Held;

	// Checks to see if the item is to be lifted >
	if (bLiftItem)
	{
		// If so, lift the item and stop after 'x' seconds.
		GetWorldTimerManager().SetTimer(m_Timer, this, &AItem_Base::LiftComplete, fLiftDuration, false);
	}

	// Reference the player.
	if (!m_PlayerCharacter)
	{
		m_PlayerCharacter = rPlayerCharacter;
	}

	// Calls held to set the properties.
	Held();
}

void AItem_Base::Held()
{
	bItemHeld = true;

	if (bLiftItem)
	{
		// Sets the lift position based on the items current position.
		m_v3LiftPosition = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + fLiftHeight);
	}

	// Set the properties to allow for tracking to be enabled.
	bHasTarget = true;
	bThrown = false;

	Mesh->SetSimulatePhysics(true);

	// Disable gravity to allow for object to be pulled/pushed towards destination.
	Mesh->SetEnableGravity(false);

	// Add linear damping so the pull seems more in control.
	Mesh->SetLinearDamping(fPullDrag);
	Mesh->SetAngularDamping(fHeldDrag);

	// Custom collision profile to ignore allows for the linetrace to ignore the object.
	Mesh->SetCollisionProfileName("ItemHeld");

	// This function is called to start shaking the item when held.
	GetWorldTimerManager().SetTimer(m_ShakeTimer, this, &AItem_Base::Shake, 0.1f, false);
}

void AItem_Base::Shake()
{
	// Create a force to apply to the mesh.
	FVector v3ShakeForce = UKismetMathLibrary::RandomUnitVector() * fShakeForce;

	// Check that the object has not been thrown.
	if (Mesh->IsSimulatingPhysics() && !bThrown)
	{
		// Add an impulse every time this function is called.
		Mesh->AddImpulse(v3ShakeForce, NAME_None, true);
	}

	// Clear and recall the timer.
	GetWorldTimerManager().ClearTimer(m_ShakeTimer);
	GetWorldTimerManager().SetTimer(m_ShakeTimer, this, &AItem_Base::Shake, 0.05f, false);
}

void AItem_Base::Dropped()
{
	// Clear the timer.
	GetWorldTimerManager().ClearTimer(m_ShakeTimer);

	// Stop the item from tracking the target.
	bHasTarget = false;

	// Reset held state.
	bItemHeld = false;

	// Reset lift complete as if interacted with again, it will need to be lifted.
	m_bLiftComplete = false;

	// Reset its state.
	m_eCurrentState = ItemState::Default;

	// Enable gravity as the item has been thrown/dropped.
	Mesh->SetSimulatePhysics(true);

	// Enable gravity as the item has been thrown/dropped.
	Mesh->SetEnableGravity(true);

	// Reset the linear damping.
	Mesh->SetLinearDamping(0);
	Mesh->SetAngularDamping(0.01f);

	// Reset collision profile to allow for linetrace detection.
	Mesh->SetCollisionProfileName("PhysicsActor");
}

void AItem_Base::TrackTarget()
{

}

void AItem_Base::LiftItem()
{
	if (!m_bLiftComplete)
	{
		// Create a vector of Target - Current position.
		FVector v3TargetPos = m_v3LiftPosition - GetActorLocation();

		// Clamp the speed of an object based on it's mass.
		float fSpeedClamp = MapRangedClamped(Mesh->GetMass(), 0, 10, 0, fLiftSpeed);

		// Add a constant impulse dependant on the clamped speed value.
		Mesh->AddImpulse(v3TargetPos.GetClampedToSize(0, 1000) * (fSpeedClamp * 100) * fDeltaTime);
	}
}

void AItem_Base::PullItem()
{
	// Create a vector of Target - Current position.
	FVector v3TargetPos = m_PlayerCharacter->GetHeldPosition()->GetComponentLocation() - GetActorLocation();

	// Clamp the speed of an object based on it's mass.
	float fSpeedClamp = MapRangedClamped(Mesh->GetMass(), 0, 10, 0, fPullSpeed);

	// Add a constant impulse dependant on the clamped speed value.
	Mesh->AddImpulse(v3TargetPos.GetClampedToSize(0, 1000) * (fSpeedClamp * 100) * fDeltaTime);
}

float AItem_Base::MapRangedClamped(float fValue, float fInRangeA, float fInRangeB, float fOutRangeA, float fOutRangeB)
{
	// Used to reassign one range of numbers to another based on the input value.
	// Example:
	// If value is 25, in range 0, out range 100.
	// (25 - 0) / (0 - 100) = 25 / -100 = -0.25.
	// This means that it will return clamp value outRangeA.

	// If a out A is equal to out B, return either as they are the same value.
	if (fOutRangeA == fOutRangeB)
	{
		return fOutRangeA;
	}

	// Calculates the clamp value to apply to the object dependant on the mass.
	float inPercentage = (fValue - fInRangeA) / (fInRangeB - fInRangeA);

	// Return if the value is less than 0.
	if (inPercentage < 0.0f)
	{
		return fOutRangeA;
	}

	// Return if the value is greater than 0.
	if (inPercentage > 1.0f)
	{
		return fOutRangeB;
	}

	return fOutRangeA + inPercentage * (fOutRangeB - fOutRangeA);
}

void AItem_Base::LiftComplete()
{
	m_bLiftComplete = true;
}

bool AItem_Base::GetIsThrown()
{
	// Return whether or not the item has been thrown.
	return bThrown;
}

UStaticMeshComponent* AItem_Base::GetMesh()
{
	return Mesh;
}

FString AItem_Base::GetTag()
{
	return Tag;
}

void AItem_Base::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// If an object is hit after the player has thrown it >
	if (bThrown && !OtherActor->IsA<APlayerCharacter>())
	{
		// > then reset the item properties.
		Dropped();
	}
}

FVector AItem_Base::MoveTowardsLocation(FVector v3Current, FVector v3Target, float fMaxDistanceDelta)
{
	// Get the target position.
	FVector TargetPos = v3Target - v3Current;

	float Delta = fMaxDistanceDelta * fDeltaTime;

	// Distance between two points.
	float Distance = TargetPos.Size();

	if (Distance <= Delta || Distance == 0.f)
	{
		return v3Target;
	}

	// Return the new position after applying the target position.
	return v3Current + TargetPos / Distance * Delta;
}
