// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_TimerStart.h"
#include "Radiance/LoopManager.h"

#include "Kismet/GameplayStatics.h"
#include <Components/BoxComponent.h>

ATriggerVolume_TimerStart::ATriggerVolume_TimerStart()
{
}

void ATriggerVolume_TimerStart::BeginPlay()
{
	// Call the base class's begin play function, which would be the AActor's one as the TriggerVolume_Base does not have one.
	// (Nikodem Hamrol)
	Super::BeginPlay();

	// Setup an OnComponentBeginOverlap callback function to be called when an overlap is triggered. (Nikodem Hamrol)
	m_BoxTriggerVolume->OnComponentBeginOverlap.AddDynamic( this, &ATriggerVolume_TimerStart::OnBeginOverlapTrigger );
	
	// Get the loop manager instance in the level
	m_LoopManager = Cast<ALoopManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ALoopManager::StaticClass()));

	// Subscribe to the Reset for next cycle delegate from the loop manager
	if (m_LoopManager != nullptr)
	{
		m_LoopManager->OnResetForNextCycle.AddUObject(this, &ATriggerVolume_TimerStart::ResetForNextCycle_Implementation);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("NO LOOP MANAGER BLUEPRINT IN THE LEVEL"));
	}

}

void ATriggerVolume_TimerStart::OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit )
{
	if (OtherActor->Tags.Contains("Player") && m_LoopManager)
	{
		// Start a new cycle
		m_LoopManager->StartCycle();

		// Set trigger volume to not be collidable
		m_BoxTriggerVolume->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ATriggerVolume_TimerStart::ResetForNextCycle_Implementation(const int32 CurrentCycle)
{
	// Set trigger volume to be collidable only for queries
	m_BoxTriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// Broadcast that the object finished its reset
	OnFinishedResetting.ExecuteIfBound();
}
