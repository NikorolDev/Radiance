// Fill out your copyright notice in the Description page of Project Settings.

#include "Terminal.h"
#include "Radiance/Access/Access.h"
#include "Radiance/Lifts/Lift_Terminal.h"

// Sets default values
ATerminal::ATerminal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a static mesh component and set its properties.
	TerminalMesh = CreateDefaultSubobject<UStaticMeshComponent>("Terminal");
	TerminalMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = TerminalMesh;

	// Create a static mesh component and set its properties.
	TerminalButton = CreateDefaultSubobject<UStaticMeshComponent>("Terminal Button");
	TerminalButton->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	TerminalButton->SetupAttachment(TerminalMesh);
}

void ATerminal::OnInteract_Implementation(AActor* Caller)
{
	for (AAccess* i : Access)
	{
		i->TerminalActivated();
	}
}

// Called when the game starts or when spawned
void ATerminal::BeginPlay()
{
	Super::BeginPlay();

	for (AAccess* i : Access)
	{
		if (i->IsA<ALift_Terminal>())
		{
			ALift_Terminal* AccessRef = Cast<ALift_Terminal>(i);
			RootComponent->AttachToComponent(AccessRef->GetTerminalPosition(), FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}

// Called every frame
void ATerminal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
