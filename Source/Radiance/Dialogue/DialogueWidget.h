// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

// Forward class declarations
class URichTextBlock;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UDialogueWidget
// Author				: Nikodem Hamrol
// Classes Inherited	: UUserWidget
// Purpose				: This class will be responsible to display the dialogue text onto the screen. As well as 
//						,	appearing when the dialogue sequence starts and hiding when the sequence finishes
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: DisplayText( FString* psDialogueText )
	// Author			: Nikodem Hamrol
	// Purpose			: To set the widget to visible when the dialogue sequence starts and 
	//					,	display the text that is passed from the dialogue manager onto the screen.
	// Parameters		: psCharacterName	- The name of the character that speaks.
	//					, psText			- The dialogue text that needs to be displayed.
	//-----------------------------------------------------------------------------------------------------------------------------
	void DisplayText( FString& psCharacterName, FString& psText );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: HideDialogue()
	// Author			: Nikodem Hamrol
	// Purpose			: To hide the widget when the dialogue finishes
	//-----------------------------------------------------------------------------------------------------------------------------
	void HideDialogue();

protected:	
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: NativeConstruct() override
	// Author			: UE4
	// Editors			: Nikodem Hamrol
	// Purpose			: This is the constructor to the widget, which is similar to the "Event Construct" in Blueprint Widget.
	//					,	It is used to hide itself when starting the game.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void NativeConstruct() override;

private:
	// This will check if the dialogue is already displayed on the screen.
	bool m_bIsDialogueDisplayed;

	// The text block component that will display the text.
	UPROPERTY( meta = ( BindWidget ) )
		URichTextBlock* DialogueText;
};
