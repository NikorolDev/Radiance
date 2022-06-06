// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SplashSceneWidget.generated.h"

UCLASS()
class RADIANCE_API USplashSceneWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	// Fade Animation. (Michalis Stratis)
	//UPROPERTY ( Transient, meta = ( BindWidgetAnim ) )
		//UMediaPlayer* SplashVideo;

	// Fade Animation. (Michalis Stratis)
	//UPROPERTY ( Transient, meta = ( BindWidgetAnim ) )
		//USoundBase* SplashSound;

	// Fade Animation. (Michalis Stratis)
	//UPROPERTY ( Transient, meta = ( BindWidgetAnim ) )
		//UImage* SplashScreenVideo;

};
