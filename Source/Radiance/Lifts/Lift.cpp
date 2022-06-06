// Fill out your copyright notice in the Description page of Project Settings.

#include "Lift.h"
#include "Radiance/Access/Switch.h"
#include "Radiance/Doors/Door.h"
#include <Kismet/GameplayStatics.h>
#include "Components/PointLightComponent.h"

ALift::ALift()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a static mesh component and set its properties.
	Pivot = CreateDefaultSubobject<USceneComponent>("Pivot");
	RootComponent = Pivot;

	// Create a static mesh component and set its properties.
	LiftMesh = CreateDefaultSubobject<UStaticMeshComponent>("Lift");
	LiftMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LiftMesh->SetupAttachment(Pivot);

	// Create a static mesh component and set its properties.
	SlotPosition = CreateDefaultSubobject<USceneComponent>("Slot Point");
	SlotPosition->SetupAttachment(LiftMesh);

	// Create and set the properties of the light component used for indicating the lift state.
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(LiftMesh);
}

void ALift::BeginPlay()
{
	Super::BeginPlay();

	// Retrieve all actors which can be influenced by the cycles (by design they all implement UInfluentiableThroughCycles interface
	TArray<AActor*> TempSwitches;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASwitch::StaticClass(), TempSwitches);

	for (AActor* Switch : TempSwitches)
	{
		// Store all the influentiable actors
		Switches.Add(Cast<ASwitch>(Switch));

		// Subscribe to the Finished Resetting delegate from the influentiable actor
		Switches.Last()->OnButtonPressed.BindUObject(this, &ALift::LiftCalled);
	}
}

USceneComponent* ALift::GetSlotPosition()
{
	// Returns the slot position.
	return SlotPosition;
}

void ALift::MotionHandler()
{
	// Handles the animation of the lift by accessing the current timeline attached to the class.
	m_fTimelineValue = m_Timeline.GetPlaybackPosition();
	m_fCurveFloatValue = AnimationCurve->GetFloatValue(m_fTimelineValue);

	// Create the new position.
	FVector v3NewPosition = FVector(0, 0, m_fCurveFloatValue);

	// Set the new position.
	LiftMesh->SetRelativeLocation(v3NewPosition);
}

void ALift::MotionFinished()
{
	if (bIsUp)
	{
		Doors[0]->GetTimeline()->Play();
	}
	else
	{
		Doors[0]->GetTimeline()->Reverse();
		Doors[1]->GetTimeline()->Play();
	}
}

void ALift::LiftCalled(FString sMessage)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));

	if (sMessage == "DoorUp")
	{
		bIsUp = true;
		m_Timeline.Play();

	}
	else
	{
		bIsUp = false;
		m_Timeline.Reverse();
	}
}
