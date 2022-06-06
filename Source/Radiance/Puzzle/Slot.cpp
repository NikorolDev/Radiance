// Fill out your copyright notice in the Description page of Project Settings.


#include "Slot.h"
#include "Radiance/Items/Item_ThrowableModule.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "Radiance/Doors/Door_Module.h"
#include "Radiance/Lifts/Lift_Module.h"
#include "Radiance/Access/Access.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASlot::ASlot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a static mesh component and set its properties.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetEnableGravity(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = Mesh;

	// Creates a trigger used to detect when the player is in range.
	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	Collider->SetupAttachment(Mesh);

	// Reference the position where the objects will 'AttachPosition'.
	AttachPosition = CreateDefaultSubobject<USceneComponent>("Attach Position");
	AttachPosition->SetupAttachment(Mesh);
	AttachPosition->SetVisibility(false);

	// Create a static mesh component and set its properties.
	LightBox = CreateDefaultSubobject<UStaticMeshComponent>("LightBox");
	LightBox->SetupAttachment(Mesh);

	// Creates a light component to indicate the current state of the slot to the player.
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(LightBox);

	// Allow the slot to attach a module.
	m_bCanAttach = true;
}

// Called when the game starts or when spawned
void ASlot::BeginPlay()
{
	Super::BeginPlay();

	// Setup an OnComponentBeginOverlap callback function to be called when an overlap is triggered.
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ASlot::OnBeginOverlapTrigger);

	// Setup an OnComponentEndOverlap callback function to be called when an overlap is ended.
	Collider->OnComponentEndOverlap.AddDynamic(this, &ASlot::OnEndOverlapTrigger);

	// Change the color of the light.
	Light->SetLightColor(FLinearColor(FColor::FromHex("FFA758FF")));

	for (AAccess* i : Access)
	{
		// Check to see if the referenced access class is a 'Lift_Module'... if true, attach to position.
		if (i->IsA<ALift_Module>())
		{
			ALift_Module* AccessRef = Cast<ALift_Module>(i);
			RootComponent->AttachToComponent(AccessRef->GetSlotPosition(), FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}

// Called every frame
void ASlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASlot::CheckCollisionType(AActor* pcObject, FString Name)
{
	// Check to see if the item is the module.
	if (pcObject->IsA<AItem_ThrowableModule>())
	{
		// Cast to the object.
		m_pcModule = Cast<AItem_ThrowableModule>(pcObject);

		// Check that the tag of the module is the same as the name passed as a parameter.
		if (m_pcModule->GetTag() == FString(Name))
		{
			return true;
		}
	}
	return false;
}

void ASlot::OnBeginOverlapTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	// Checks the type of collision.
	if (CheckCollisionType(OtherActor, FString("Module")))
	{
		// Makes sure the module can be attached.
		if (m_pcModule && !m_bHasModule && m_bCanAttach && m_pcModule->GetIsThrown())
		{
			// Set the correct properties.
			m_bHasModule = true;
			m_bCanAttach = false;

			// Attach the module to the attach position.
			m_pcModule->Attach(AttachPosition);

			// Change the color of the light.
			Light->SetLightColor(FLinearColor::Green);

			// Play charged audio sound to indicate to player that the gauntlet is charged.
			UGameplayStatics::PlaySound2D(GetWorld(), ActiveSFX, 1);

			for (AAccess* i : Access)
			{
				// Call the module attached function to alert the access class a module has been attached.
				i->ModuleAttached();
			}
		}
	}
}

void ASlot::OnEndOverlapTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (CheckCollisionType(OtherActor, FString("Module")) && m_bHasModule)
	{
		// No longer has a module attached.
		m_bHasModule = false;

		// Disable the collider temporarily.
		Collider->SetActive(false);

		// Change the color of the slot.
		Light->SetLightColor(FLinearColor::Red);

		for (AAccess* i : Access)
		{
			// Called the module detached function to alert the access class a module has been detached.
			i->ModuleDetached();
		}

		// Play charged audio sound to indicate to player that the gauntlet is charged.
		UGameplayStatics::PlaySound2D(GetWorld(), InactiveSFX, 1);

		// Call a timer to reset the slots state.
		GetWorldTimerManager().SetTimer(m_CooldownTimer, this, &ASlot::ResetCanAttach, 2.f, false);
	}
}

void ASlot::ResetCanAttach()
{
	// Enable the collider.
	Collider->SetActive(true);

	// Allow a module to be attached.
	m_bCanAttach = true;

	// Change the color of the light.
	Light->SetLightColor(FLinearColor(FColor::FromHex("FFA758FF")));
}

bool ASlot::CheckForModule()
{
	return m_bHasModule;
}
