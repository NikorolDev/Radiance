#pragma once

#include "Struct_PuzzleProperties.h"
#include "Struct_Puzzle.generated.h"

//----------------------------------------------------------------------------------------------------------------------------
// Struct Name			: FStructPuzzle
// Author				: Kurtis Watson
// Purpose				: Create an array of puzzle properties.
//----------------------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FStructPuzzle
{
	GENERATED_BODY()

		// The dialogue sequence that will displayed on the screen.
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		TArray<struct FStructPuzzleProperties> PuzzleProperties;
};