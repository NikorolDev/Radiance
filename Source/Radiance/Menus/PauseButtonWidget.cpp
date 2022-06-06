// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseButtonWidget.h"
#include "Components/Button.h"
#include "PauseMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UPauseButtonWidget::NativeConstruct ( )
{
	Super::NativeConstruct ( );

	//Creating the Pause Menu Widget 
	PauseWidget = CreateWidget<UPauseMenuWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0),
												m_pcPauseWidget);

	// On click functionality of the buttons created
	PauseButton->OnClicked.AddDynamic ( this, &UPauseButtonWidget::PauseButtonClicked );
}

UPauseButtonWidget::~UPauseButtonWidget ( )
{
}

void UPauseButtonWidget::PauseButtonClicked ( )
{	
	//UGameplayStatics::SetGamePaused(GetWorld( ), true );
	if ( PauseWidget != nullptr ) 
	{
		// Adding the MenuWidget on the screen 
		PauseWidget->AddToViewport();
	}	
}
