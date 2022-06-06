// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget_Base.h"
#include "GameOverMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class RADIANCE_API UGameOverMenuWidget : public UMenuWidget_Base
{
	GENERATED_BODY()

protected:
	UPROPERTY ( meta = ( BindWidget ) )
		class UButton* PlayAgain;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: NativeConstruct()
	// Author			: Michalis Stratis
	// Purpose			: 
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void NativeConstruct() override;

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ~UGameOverMenuWidget()
	// Author			: Michalis Stratis
	// Purpose			: UMain_MenuWidget destructor
	//-----------------------------------------------------------------------------------------------------------------------------
	~UGameOverMenuWidget ( );

	UGameOverMenuWidget ( );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: PlayAgainButtonClicked()
	// Author			: Michalis Stratis
	// Purpose			: The functionality of the play button when clicked 
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void PlayAgainButtonClicked();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: PlayAgainButtonHovered()
	// Author			: Michalis Stratis
	// Purpose			: The functionality of the play button when hovered 
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void PlayAgainButtonHovered();
	
};
