// Fill out your copyright notice in the Description page of Project Settings.
//-----------------------------------------------------------------------------------------------------------------------------
// Class Name		    : LightSwitch
// Author				: Michalis Stratis
// Editors				: Michalis Stratis
// Purpose              : To turn a specific point light on and off (Light Switch)


#include "LightSwitch.h"
#include "Components/SphereComponent.h"
#include "Components/ActorComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PointLightCollider.h"
#include "Player/PlayerCharacter.h"
#include "DrawDebugHelpers.h"

// Sets default values
ALightSwitch::ALightSwitch()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create sphere component and set collisions enabled
	LightSwitchCollider = CreateDefaultSubobject<UStaticMeshComponent> ( TEXT ( "STATIC MESH COMPONENT" ) );
	LightSwitchCollider->SetCollisionEnabled ( ECollisionEnabled::QueryAndPhysics );
	LightSwitchCollider->Activate ( true );
	LightSwitchCollider->SetCollisionResponseToAllChannels ( ECollisionResponse::ECR_Overlap );

	// Setting Sphere Collider Overlap events 
	LightSwitchCollider->OnComponentBeginOverlap.AddDynamic ( this, &ALightSwitch::OnOverlapBegin );
	LightSwitchCollider->OnComponentEndOverlap.AddDynamic ( this, &ALightSwitch::OnOverlapEnd );

	// Creating Point Light and setting its intensity 
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	m_fLightIntensity = 1600.0f;
	PointLight->Intensity = m_fLightIntensity;

	// Setting Point Light as root component
	RootComponent = PointLight;

}

// Called when the game starts or when spawned
void ALightSwitch::BeginPlay()
{
	Super::BeginPlay();

	// Drawing Debug Sphere around actor  
	//DrawDebugSphere(GetWorld(), GetActorLocation(), 200.0f, 50, FColor::Green, true, 999, 0, 2);

}

// Called every frame
void ALightSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALightSwitch::OnOverlapBegin ( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	// If the Player Character has overlapped with the collider, add appropriate message on screen
	if ( OtherActor->IsA<APlayerCharacter> () )
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("THE PLAYER IN LIGHT SWITCH")	);
		PointLight->ToggleVisibility (  );
	}

}

void ALightSwitch::OnOverlapEnd ( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex )
{
	// If the Player Character overlap with the collider has ended, add appropriate message on screen
	if ( OtherActor->IsA<APlayerCharacter> () )
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("THE PLAYER IN LIGHT SWITCH")	);
		PointLight->ToggleVisibility (  );
	}

}

void ALightSwitch::ToggleLight ( )
{
	// Change the vissibility state of the PointLight
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("YOU PRESSED L INSIDE THE COLLIDER")	);
	PointLight->ToggleVisibility ( );
}


