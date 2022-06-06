#pragma once

#include "Struct_DialogueProperties.h"
#include "Struct_DialogueSequence.generated.h"

//----------------------------------------------------------------------------------------------------------------------------
// Struct Name			: FStructDialogueSequence
// Author				: Nikodem Hamrol
// Purpose				: This struct is made to store the array of the dialogue properties to be used in the TMap in the 
//						,	dialogue manager.
//----------------------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FStructDialogueSequence
{
	GENERATED_BODY()

	// The dialogue sequence that will displayed on the screen.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
		TArray<struct FStructDialogueProperties> DialogueSequence;
};