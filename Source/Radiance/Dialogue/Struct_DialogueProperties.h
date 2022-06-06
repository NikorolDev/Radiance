#pragma once

#include "Struct_DialogueProperties.generated.h"

//Forward class declaration
class USoundWave;

//----------------------------------------------------------------------------------------------------------------------------
// Struct Name			: FStructDialogueProperties
// Author				: Nikodem Hamrol
// Purpose				: This struct is made to store the properties of each dialogue, such as text and duration of display 
//						,	and audio files.
//----------------------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FStructDialogueProperties
{
	GENERATED_BODY()

	// The audio that will play for the dialogue.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
		USoundWave* DialogueAudio = nullptr;

	// The character name to display on screen.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
		FString		CharacterName = FString("");

	// The text to display on screen.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
		FString		DialogueText = FString("");

	// The extra time to delay the next dialogue term playing.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
		float		DialogueDurationOffset = 0.0f;
};
