// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget_Base.h"
#include "MainMenuWidget.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AMainMenuWidget
// Author				: Michalis Stratis
// Classes Inherited	: UUserWidget
// Purpose				: This class will hold the widget for the main menu 
//-----------------------------------------------------------------------------------------------------------------------------
class UOptionsMenuWidget;
class UFadeAnimationWidget;
class USplashSceneWidget;

UCLASS()
class RADIANCE_API UMainMenuWidget : public UMenuWidget_Base
{
	GENERATED_BODY()

protected:

	UPROPERTY ( meta = ( BindWidget ) )
		class UButton*											StartGame;

	UPROPERTY ( meta = ( BindWidget ) )
		class UButton*											Options;

	UPROPERTY( EditDefaultsOnly,BlueprintReadWrite )
		TSubclassOf<UOptionsMenuWidget>							m_pcOptionsWidget;


	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: NativeConstruct()
	// Author			: Michalis Stratis
	// Purpose			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void NativeConstruct() override;

public:

	UOptionsMenuWidget* OptionsWidget;

	UFadeAnimationWidget* FadeWidget;

	USplashSceneWidget* SplashWidget;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ~UMain_MenuWidget()
	// Author			: Michalis Stratis
	// Purpose			: UMain_MenuWidget destructor
	//-----------------------------------------------------------------------------------------------------------------------------
	~UMainMenuWidget ( );
	UMainMenuWidget ( );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: StartGameButtonClicked()
	// Author			: Michalis Stratis
	// Purpose			: The functionality of the play button when clicked 
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void StartGameButtonClicked();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: StartGameButtonClicked()
	// Author			: Michalis Stratis
	// Purpose			: The functionality of the play button when clicked 
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void StartGameButtonHovered();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OptionsButtonClicked()
	// Author			: Michalis Stratis
	// Purpose			: The functionality of the options button when clicked 
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable)
		void OptionsButtonClicked();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: StartGameButtonClicked()
	// Author			: Michalis Stratis
	// Purpose			: The functionality of the play button when clicked 
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void  OptionsButtonHovered();


};
