#pragma once

#include "Struct_PuzzleProperties.generated.h"

class AActor;

//----------------------------------------------------------------------------------------------------------------------------
// Struct Name			: FStructPuzzleProperties
// Author				: Kurtis Watson
// Purpose				: The puzzle properties.
//----------------------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FStructPuzzleProperties
{
	GENERATED_BODY()
	
	// ID of the puzzle/
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		int ID;

	// Name of the puzzle.
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		FString PuzzleName;

	// Time to complete the puzzle.
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		float TimeToComplete;

	// Tasks required in order to complete puzzle.
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		int TasksRequired;

	// Reference to the door.
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		AActor* Door;
};
