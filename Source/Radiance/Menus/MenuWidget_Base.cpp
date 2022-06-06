// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget_Base.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuWidget_Base::NativeConstruct ( )
{
	// Call the native construct from the UUserWidget.
	Super::NativeConstruct ( );

	// On click functionality of the buttons created
	QuitGame->OnClicked.AddDynamic ( this, &UMenuWidget_Base::QuitGameButtonClicked );
	QuitGame->OnHovered.AddDynamic ( this, &UMenuWidget_Base::QuitGameButtonHovered );
}

UMenuWidget_Base::~UMenuWidget_Base ( )
{
}

void UMenuWidget_Base::QuitGameButtonClicked ( )
{
	//Play UI sound when the cursor is over the button 
	PlayUISound ( m_pcButtonClickedSound );

	// UE_LOG message
	UE_LOG ( LogTemp, Warning, TEXT ( "QUIT BUTTON" ));
	ExitGame ( );
}


void UMenuWidget_Base::QuitGameButtonHovered ( )
{
	PlayUISound ( m_pcButtonHoveredSound );
}

void UMenuWidget_Base::ShowMenu ( )
{
	// Setting the Main Menu Visible and adding it on the screen 
	this->SetVisibility ( ESlateVisibility::Visible );
}

void UMenuWidget_Base::HideMenu ( )
{
	// Setting the Main Menu hidden and removing it from the screen 
	this->SetVisibility( ESlateVisibility::Hidden );
}

void UMenuWidget_Base::GoToMap (  FName level )
{
	UGameplayStatics::OpenLevel ( this, level );
}

void UMenuWidget_Base::ExitGame ( )
{
	// Exiting the game 
	UKismetSystemLibrary::QuitGame ( GetWorld(), PC, EQuitPreference::Quit , false );
}

void UMenuWidget_Base::PlayUISound ( USoundBase* UIAudio )
{
	UGameplayStatics::PlaySound2D ( GetWorld ( ), UIAudio, 1.0f );
}
