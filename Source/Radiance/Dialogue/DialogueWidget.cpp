// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueWidget.h"

#include <Components/RichTextBlock.h>

void UDialogueWidget::NativeConstruct()
{
	// Call the native construct from the UUserWidget.
	Super::NativeConstruct();

	// Hide the dialogue widget so it is not visible when the player starts the game.
	HideDialogue();
}

void UDialogueWidget::DisplayText( FString& psCharacterName, FString& psText )
{
	// Check if this widget is not displayed.
	if( !m_bIsDialogueDisplayed )
	{
		// Set the dialogue text to be visible and the bool to be true so this code does not get called when the 
		// dialogue sequence is still playing.
		SetVisibility( ESlateVisibility::Visible );
		m_bIsDialogueDisplayed = true;
	
		UE_LOG( LogTemp, Display, TEXT( "Widget Displayed" ) );
	}

	// Set the text of the dialogue with the character name.
	// Concatenate the so the character name can be manipulated via "DT_WidgetTextData", which holds how text should look like.
	DialogueText->SetText( FText::FromString( "<Character>" + psCharacterName + "</>: " + psText ) );
	UE_LOG( LogTemp, Display, TEXT( "New Dialogue Set" ) );
}

void UDialogueWidget::HideDialogue()
{
	// Set visibility of the dialogue to be hidden and set the boolean to be false, so it can be redisplayed.
	SetVisibility( ESlateVisibility::Hidden );
	m_bIsDialogueDisplayed = false;

	UE_LOG( LogTemp, Display, TEXT( "Hidden Menu" ) );
}