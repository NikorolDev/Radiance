// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "MainMenuWidget.h"
#include "OptionsMenuWidget.h"
#include "Components/Button.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Radiance/Player/PlayerCharacter.h"

void UPauseMenuWidget::NativeConstruct ( )
{
	// Call the native construct from the UUserWidget.
	Super::NativeConstruct ( );
	 
	// Creating the Main Menu Widget 
	MenuWidget = CreateWidget<UMainMenuWidget>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ), 
												 m_pcMenuWidget );

	// Creating the Options Menu Widget 
	OptionsWidget = CreateWidget<UOptionsMenuWidget>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ), 
												 m_pcOptionsWidget );

	// Adding OptionMenuOnTheScreen and setting it to hidden 
	OptionsWidget->AddToViewport ( );
	OptionsWidget->SetVisibility ( ESlateVisibility::Hidden );

	// On click functionality of the ReturnToMainMenu button 
	ReturnToMainMenu->OnClicked.AddDynamic ( this, &UPauseMenuWidget::MainMenuButtonClicked );
	ReturnToMainMenu->OnHovered.AddDynamic ( this, &UPauseMenuWidget::MainMenuButtonHovered );

	// On click functionality of the Resume button 
	ResumeButton->OnClicked.AddDynamic ( this, &UPauseMenuWidget::ResumeButtonClicked );
	ResumeButton->OnHovered.AddDynamic ( this, &UPauseMenuWidget::ResumeButtonHovered );

	// On click functionality of the Options button 
	Options->OnClicked.AddDynamic ( this, &UPauseMenuWidget::OptionsButtonClicked );
	Options->OnHovered.AddDynamic ( this, &UPauseMenuWidget::OptionsButtonHovered );

}

UPauseMenuWidget::~UPauseMenuWidget ( )
{
}

void UPauseMenuWidget::MainMenuButtonHovered ( )
{
	PlayUISound ( m_pcPauseHoveredSound );
}

void UPauseMenuWidget::MainMenuButtonClicked ( )
{
	PlayUISound ( m_pcButtonClickedSound );

	PlayAnimation ( FadeOut );

	if ( MenuWidget != nullptr ) 
	{
		GetWorld ( )->GetTimerManager ( ).SetTimer ( TimerHandle, [ & ] ()
			{
				 // Opening the final map (Michalis Stratis)
				 UGameplayStatics::OpenLevel ( this, "Map_MainMenuEnd" );

			}, 2, false );
	}
}


void UPauseMenuWidget::OptionsButtonHovered ( )
{
	PlayUISound ( m_pcPauseHoveredSound );
}

void UPauseMenuWidget::OptionsButtonClicked ( )
{
	PlayUISound ( m_pcOptionsButtonClickedSound );

	if ( OptionsWidget != nullptr )
	{
		OptionsWidget->SetPreviousAccessedWidget ( this );
		SetVisibility ( ESlateVisibility::Hidden );
		OptionsWidget->SetVisibility ( ESlateVisibility::Visible );
	}
	
}

void UPauseMenuWidget::ResumeButtonHovered ( )
{
	PlayUISound ( m_pcPauseHoveredSound );
}

void UPauseMenuWidget::SetPlayerCharacter(APlayerCharacter* pcPlayer)
{
	m_pcPlayer = pcPlayer;
}

void UPauseMenuWidget::ResumeButtonClicked ( )
{
	PlayUISound ( m_pcButtonClickedSound );
	m_pcPlayer->DisablePauseMenu();
	UGameplayStatics::SetGamePaused(GetWorld( ), false );

}
