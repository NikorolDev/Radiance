// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "OptionsMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "FadeAnimationWidget.h"
#include "SplashSceneWidget.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeConstruct ( )
{
	Super::NativeConstruct ( );

	// Play Fade In Animation
	PlayAnimation ( FadeIn );

	// Creating the Options Widget 
	OptionsWidget = CreateWidget<UOptionsMenuWidget>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ), 
													  m_pcOptionsWidget );
	OptionsWidget->AddToViewport ( );

	OptionsWidget->SetVisibility ( ESlateVisibility::Hidden );

	// On click functionality of the buttons created
	StartGame->OnClicked.AddDynamic ( this, &UMainMenuWidget::StartGameButtonClicked );
	//StartGame->OnHovered.AddDynamic ( this, &UMainMenuWidget::StartGameButtonHovered );
	Options->OnClicked.AddDynamic ( this, &UMainMenuWidget::OptionsButtonClicked );
	//Options->OnHovered.AddDynamic ( this, &UMainMenuWidget::OptionsButtonHovered );
}

UMainMenuWidget::~UMainMenuWidget ( )
{
}

UMainMenuWidget::UMainMenuWidget ( )
{
}

void UMainMenuWidget::StartGameButtonHovered ( )
{
	this->PlayUISound ( m_pcButtonHoveredSound );
}

void UMainMenuWidget::StartGameButtonClicked ( )
{
	// UE_LOG message
	UE_LOG ( LogTemp, Warning, TEXT ( "PLAY BUTTON" ) );

	//Play Sound 
	this->PlayUISound ( m_pcButtonClickedSound );

	//Play Fade Out Animation
	PlayAnimation ( FadeOut );

	GetWorld ( )->GetTimerManager ( ).SetTimer ( TimerHandle, [ & ] ( )
												 {
													 // Calling the HideMenu() function and opening a different map 
													 this->HideMenu ( );
													 this->RemoveFromParent ( );
													 this->GoToMap ( "Persistent_Map" );

												 }, 1.8, false );
	
}

void UMainMenuWidget::OptionsButtonHovered ( )
{
	this->PlayUISound ( m_pcOptionsButtonClickedSound );
}

void UMainMenuWidget::OptionsButtonClicked ( )
{
	//this->PlayUISound ( m_pcButtonClickedSound );
	if ( OptionsWidget != nullptr ) 
	{
		// UE_LOG message
		UE_LOG ( LogTemp, Warning, TEXT ( "Options" ));

		OptionsWidget->SetPreviousAccessedWidget ( this );
		SetVisibility ( ESlateVisibility::Hidden );
		OptionsWidget->SetVisibility ( ESlateVisibility::Visible );
	}
}




