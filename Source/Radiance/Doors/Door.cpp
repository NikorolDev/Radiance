// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "Radiance/Player/PlayerCharacter.h"
#include "Radiance/Doors/Door_Terminal.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PointLightComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a box component and set its properties.
	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	RootComponent = DoorFrameMesh;

	// Blocker to block the player.
	Blocker = CreateDefaultSubobject<UBoxComponent>("Blocker");
	Blocker->SetupAttachment(Collider);

	// Create a static mesh component and set its properties.
	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorFrameMesh");
	DoorFrameMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DoorFrameMesh->SetupAttachment(Collider);

	// Create a static mesh component and set its properties.
	LeftDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Left Door");
	LeftDoorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	LeftDoorMesh->SetupAttachment(DoorFrameMesh);

	// Create a static mesh component and set its properties.
	RightDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Right Door");
	RightDoorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RightDoorMesh->SetupAttachment(DoorFrameMesh);

	// Create a light component that will indicate if the door is locked or unlocked.
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(DoorFrameMesh);

	IsPlayerActivated = false;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	// Setup an OnComponentBeginOverlap callback function to be called when an overlap is triggered.
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnBeginOverlap);

	// Setup an OnComponentEndOverlap callback function to be called when an overlap is ended.
	Collider->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnEndOverlap);
}

void ADoor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	// Checks if the door is player activated.
	if (OtherActor->IsA<APlayerCharacter>() && IsPlayerActivated)
	{
		// Open the door.
		m_Timeline.Play();
	}
}

void ADoor::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA<APlayerCharacter>() && IsPlayerActivated)
	{
		// Close the door.
		m_Timeline.Reverse();
	}
}

void ADoor::ModuleAttached()
{
	Blocker->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ADoor::MotionHandler()
{
	// Get the current playback position and float value in order to translate the timeline.
	m_fTimelineValue = m_Timeline.GetPlaybackPosition();
	m_fCurveFloatValue = AnimationCurve->GetFloatValue(m_fTimelineValue);

	// Gets the new position.
	FVector v3NewPosition = FVector(0, m_fCurveFloatValue, 0);

	// Set the new relative location of the two doors.
	LeftDoorMesh->SetRelativeLocation(-v3NewPosition);
	RightDoorMesh->SetRelativeLocation(v3NewPosition);
}