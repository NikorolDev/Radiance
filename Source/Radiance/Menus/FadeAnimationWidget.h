// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FadeAnimationWidget.generated.h"

class UWidgetAnimation;
/**
 * 
 */
UCLASS()
class RADIANCE_API UFadeAnimationWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: NativeConstruct()
	// Author			: Michalis Stratis
	// Purpose			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void NativeConstruct() override;

	// Fade Animation. (Michalis Stratis)
	UPROPERTY ( Transient, BlueprintReadOnly,  meta = ( BindWidgetAnim ) )
		UWidgetAnimation* Fade_Effect;

public:
	void PlayFadeAnimation( );

	void PlayFadeReverseAnimation( );
};
