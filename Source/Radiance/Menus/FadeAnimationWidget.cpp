// Fill out your copyright notice in the Description page of Project Settings.


#include "FadeAnimationWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UFadeAnimationWidget::NativeConstruct ( )
{
	Super::NativeConstruct ( );

	PlayFadeAnimation ( );
}

void UFadeAnimationWidget::PlayFadeAnimation ( )
{
	PlayAnimation ( Fade_Effect );
}

void UFadeAnimationWidget::PlayFadeReverseAnimation ( )
{
	PlayAnimationReverse ( Fade_Effect );
}
