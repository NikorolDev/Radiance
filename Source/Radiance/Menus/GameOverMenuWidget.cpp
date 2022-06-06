// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameOverMenuWidget::NativeConstruct ( )
{

	// Call the native construct from the UUserWidget.
	Super::NativeConstruct ( );

	PlayAnimation ( FadeIn );

	// On click functionality of the buttons created
	PlayAgain->OnClicked.AddDynamic ( this, &UGameOverMenuWidget::PlayAgainButtonClicked );
	PlayAgain->OnHovered.AddDynamic ( this, &UGameOverMenuWidget::PlayAgainButtonHovered );

}

UGameOverMenuWidget::~UGameOverMenuWidget ( )
{
}

UGameOverMenuWidget::UGameOverMenuWidget ( )
{
}

void UGameOverMenuWidget::PlayAgainButtonHovered ( )
{
	// Play UI Sound when the button is hovered 
	PlayUISound ( m_pcButtonHoveredSound );
}

void UGameOverMenuWidget::PlayAgainButtonClicked ( )
{
	// Play UI Sound when the button is clicked 
	PlayUISound ( m_pcButtonClickedSound );

	this->GoToMap ( "Map_MainMenu" );
									
}





