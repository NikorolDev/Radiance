// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct_Puzzle.h"
#include "PuzzleManager.generated.h"

class ADoor;

UCLASS()
class RADIANCE_API APuzzleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// This dialogue table will hold all the dialogue in the level.
	UPROPERTY(Category = Puzzles, EditInstanceOnly, BlueprintReadOnly, meta = (DisplayName = "Puzzles"))
		TArray<FStructPuzzleProperties>		m_Puzzles;

	// 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (DisplayName = "Current Puzzle"))
		int m_iCurrentPuzzleID;

	// 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (DisplayName = "Tasks Complete"))
	int m_iTasksComplete;

	void IncrementTasksComplete();

	void DecrementTasksComplete();

	void CheckTasksComplete();

private:

};
