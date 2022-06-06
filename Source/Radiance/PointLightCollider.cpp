// Fill out your copyright notice in the Description page of Project Settings.
//-----------------------------------------------------------------------------------------------------------------------------
// Class Name		    : PointLightCollider 
// Author				: Michalis Stratis
// Editors				: Michalis Stratis
// Purpose              : To detect collsions with the light produce by the point light in the game

#include "PointLightCollider.h"
#include "Components/SphereComponent.h"
#include "Components/ActorComponent.h"
#include "Components/PointLightComponent.h"
#include "Player/PlayerCharacter.h"
#include "Enemies/Fallen/EnemyFallen.h"



// Sets default values
APointLightCollider::APointLightCollider()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create sphere component and set sphere radius
	SphereCollider=CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE COMPONENT"));
	SphereCollider->InitSphereRadius ( 40.0f );

	// Set collisions enabled and spherecollider as root component 
	SphereCollider->SetCollisionEnabled ( ECollisionEnabled::QueryAndPhysics );
	RootComponent = SphereCollider;

	// Setting Sphere Collider Overlap events
	SphereCollider->OnComponentBeginOverlap.AddDynamic ( this, &APointLightCollider::OnOverlapBegin );
	SphereCollider->OnComponentEndOverlap.AddDynamic ( this, &APointLightCollider::OnOverlapEnd );

	// Creating Point Light and setting its intensity 
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	m_fLightIntensity = 1600.0f;
	PointLight->Intensity = m_fLightIntensity;



}

// Called when the game starts or when spawned
void APointLightCollider::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APointLightCollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APointLightCollider::OnOverlapBegin ( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	// If the Player Character has overlapped with the collider, add appropriate message on screen
	if ( OtherActor->IsA<APlayerCharacter> () )
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("THE PLAYER IN LIGHT")	);
		m_bInLight = true;
		PrintOnScreen ( m_bInLight );
	}
	// If the Enemy has overlapped with the collider, add appropriate message on screen
	else if ( OtherActor->IsA<AEnemyFallen> () )
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("THE ENEMY IN LIGHT")	);
	}

}

void APointLightCollider::OnOverlapEnd ( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex )
{
	// If the Player Character overlap with the collider has ended, add appropriate message on screen
	if ( OtherActor->IsA<APlayerCharacter> () )
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("THE PLAYER OUT OF LIGHT")	);
		m_bInLight = false;
		PrintOnScreen ( m_bInLight );
	}
	// If the Enemy overlap with the collider has ended, add appropriate message on screen
	else if ( OtherActor->IsA<AEnemyFallen> () )
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("THE ENEMY OUT OF LIGHT")	);
	}
}

void APointLightCollider::PrintOnScreen ( bool bInLight )
{
	if (bInLight==true )
	{
		// Calling AddTimeFunction
		GetWorldTimerManager().SetTimer(m_TimerHandle, this, &APointLightCollider::AddTimeFunction, 1.0f, true, 2.0f);

	}
	else
	{
		// Calling DeductTime
		GetWorldTimerManager().SetTimer(m_TimerHandle, this, &APointLightCollider::DeductTime, 1.0f, true, 2.0f);
	}
}

void APointLightCollider::DisableColliders ( )
{
	// Set Collsions enabled
	SphereCollider->SetCollisionEnabled ( ECollisionEnabled::NoCollision );

}

void APointLightCollider::EnableColliders ( )
{
	// Set collisions disabled
	SphereCollider->SetCollisionEnabled ( ECollisionEnabled::QueryAndPhysics );

}


void APointLightCollider::AddTimeFunction()
{
	if (m_fCallTracker < 2)

	{
		// Reset time back to full
		m_fCallTracker = 2;
		m_fPercent = 0 + ( m_fCallTracker / 2 ) * 100;

		// Convert float to string and present it as a percentage on the screen along with message
		m_cPercentageString = FString::SanitizeFloat(m_fPercent);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, *m_cPercentageString );
		GEngine->AddOnScreenDebugMessage ( -1, 5.f, FColor::Red, TEXT ( "Full Health" ) );
	}
}

void APointLightCollider::DeductTime()
{
	if (m_fCallTracker >= 0)

	{
		// Deduct time and make it in percentage of remaining time
		m_fCallTracker--;
		m_fPercent = 0 + ( m_fCallTracker / 2 ) * 100;

		// Convert float to string and present it as a percentage on the screen
		m_cPercentageString = FString::SanitizeFloat(m_fPercent);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, *m_cPercentageString );
		if ( m_fCallTracker <= 0 )
		{
			// When time reaches zero add message on screen and set timer to 0
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT( "Full Insanity" ));
			GetWorldTimerManager ( ).ClearTimer ( m_TimerHandle );
			m_fCallTracker = 0;
		}

	}

}


