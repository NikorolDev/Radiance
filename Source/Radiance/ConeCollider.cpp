// Fill out your copyright notice in the Description page of Project Settings.
//-----------------------------------------------------------------------------------------------------------------------------
// Class Name		    : ConeCollider 
// Author				: Michalis Stratis
// Editors				: Michalis Stratis
// Purpose              : To detect collsions with the light produce by the spot light in the game

#include "ConeCollider.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/PlayerCharacter.h"
#include "Enemies/Fallen/EnemyFallen.h"
#include "Components/SpotLightComponent.h"


// Sets default values
AConeCollider::AConeCollider()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create static mesh component and set collisions enabled
	ConeCollider = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CONE COMPONENT"));
	ConeCollider->SetCollisionEnabled ( ECollisionEnabled::QueryAndPhysics );
	ConeCollider->Activate ( true );
	ConeCollider->SetCollisionResponseToAllChannels ( ECollisionResponse::ECR_Overlap );

	// Activating Overlap Events and setting conecollider as root component 
	ConeCollider->SetGenerateOverlapEvents ( true );
	RootComponent = ConeCollider;

	// Setting Cone Collider Overlap events 
	ConeCollider->OnComponentBeginOverlap.AddDynamic ( this, &AConeCollider::OnOverlapBegin );
	ConeCollider->OnComponentEndOverlap.AddDynamic ( this, &AConeCollider::OnOverlapEnd );

	// Creating Spot Light and setting its intensity 
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spot Light"));
	m_fLightIntensity = 1600.0f;
	SpotLight->Intensity = m_fLightIntensity;
;

}

// Called when the game starts or when spawned
void AConeCollider::BeginPlay()
{
	Super::BeginPlay();

}
// Called every frame
void AConeCollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AConeCollider::OnOverlapBegin ( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult )
{
	// If the Player Character has overlapped with the collider, add appropriate message on screen
	if ( OtherActor->IsA<APlayerCharacter> () )
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("THE PLAYER IN LIGHT"));
		m_bInLight = true;
		PrintOnScreen ( m_bInLight );
	}
	// If the Enemy has overlapped with the collider, add appropriate message on screen
	else if ( OtherActor->IsA<AEnemyFallen> () )
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("THE ENEMY IN LIGHT")	);
	}
}

void AConeCollider::OnOverlapEnd ( class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex )
{
	// If the Player Character overlap with the collider has ended, add appropriate message on screen
	if ( OtherActor->IsA<APlayerCharacter> () )
	{
		m_bInLight = false;
		PrintOnScreen ( m_bInLight );
	}
	// If the Enemy overlap with the collider has ended, add appropriate message on screen
	else if ( OtherActor->IsA<AEnemyFallen> () )
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("THE ENEMY OUT OF LIGHT")	);
	}

}

void AConeCollider::PrintOnScreen ( bool bInLight )
{	
	if (bInLight==true )
	{
		// Calling AddTimeFunction
		GetWorldTimerManager().SetTimer(m_TimerHandle, this, &AConeCollider::AddTimeFunction, 1.0f, true, 2.0f);
	}
	else
	{
		// Calling DeductTime
		GetWorldTimerManager().SetTimer(m_TimerHandle, this, &AConeCollider::DeductTime, 1.0f, true, 2.0f);

	}
}

void AConeCollider::DeductTime()
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

void AConeCollider::AddTimeFunction()
{
	if (m_fCallTracker < 2)

	{
		// Reset time back to full
		m_fCallTracker = 2;
		// Convert float to string and present it as a percentage on the screen along with message
		m_fPercent = 0 + ( m_fCallTracker / 2 ) * 100;
		m_cPercentageString = FString::SanitizeFloat(m_fPercent);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, *m_cPercentageString );
		GEngine->AddOnScreenDebugMessage ( -1, 5.f, FColor::Red, TEXT ( "Full Health" ) );

	}
}
