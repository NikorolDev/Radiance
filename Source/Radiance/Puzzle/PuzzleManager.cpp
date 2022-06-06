// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleManager.h"
#include "Radiance/Doors/Door.h"

// Sets default values
APuzzleManager::APuzzleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APuzzleManager::BeginPlay()
{
	Super::BeginPlay();

	//m_iCurrentPuzzleID = m_Puzzles[0].ID;
}

// Called every frame
void APuzzleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzleManager::IncrementTasksComplete()
{
	m_iTasksComplete++;
	CheckTasksComplete();
}

void APuzzleManager::DecrementTasksComplete()
{
	m_iTasksComplete--;
}

void APuzzleManager::CheckTasksComplete()
{
	if (m_iTasksComplete == m_Puzzles[m_iCurrentPuzzleID].TasksRequired)
	{
		// Reference the door for the current stage.
		ADoor* pcDoorToUnlock = Cast<ADoor>(m_Puzzles[m_iCurrentPuzzleID].Door);
		//pcDoorToUnlock->SetLockedState(false);

		m_iCurrentPuzzleID++;
	}
}

