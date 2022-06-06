// Fill out your copyright notice in the Description page of Project Settings.


#include "SplashSceneWidget.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
//#include "MediaPlayer.h"

void USplashSceneWidget::NativeConstruct ( )
{
	Super::NativeConstruct ( );
//
//	FTimerHandle TimerHandle;
//	APlayerController* PController;
//	UGameplayStatics::GetPlayerController( GetWorld(), 0 )->SetShowMouseCursor( false );
//	//UWidgetBlueprintLibrary::SetInputMode_UIOnly( PController, this, true );
//	//UGameplayStatics::PlaySound2D ( this, SplashSound, 1.f, 1.f, 0.f );
//	SetVisibility ( ESlateVisibility::Visible );
//	GetWorld ( )->GetTimerManager ( ).SetTimer ( TimerHandle, [ & ] ()
//													{
//													 this->RemoveFromParent( );
//													 UGameplayStatics::GetPlayerController( GetWorld(), 0 )->SetShowMouseCursor( true );
//
//											 },20, false );
}