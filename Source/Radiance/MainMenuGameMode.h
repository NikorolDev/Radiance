#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

class UMainMenuWidget;
class UOptionsMenuWidget;
class UGameOverMenuWidget;
class UPauseButtonWidget;
class USplashSceneWidget;
class UPauseMenuWidget;
class URadianceGameInstance;
class UFadeViewportClient;
class UWidgetAnimation;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AMainMenuGameMode
// Author				: Michalis Stratis
// Classes Inherited	: AGameModeBase
// Purpose				: This class will call the main menu widget on the screen
//-----------------------------------------------------------------------------------------------------------------------------

UCLASS()
class RADIANCE_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<UMainMenuWidget>	           m_pcMenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<UOptionsMenuWidget>	       m_pcOptionsWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<UPauseMenuWidget>	           m_pcPauseWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<UGameOverMenuWidget>          m_pcGameOverWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<USplashSceneWidget>          m_pcSplashWidget;

	// Determines if the game is starting or not
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		bool bIsStart=true;

	AMainMenuGameMode ( );

	virtual void BeginPlay ( ) override;

private:
	UMainMenuWidget* MenuWidget;

	UOptionsMenuWidget* OptionsWidget;

	UPauseMenuWidget* PauseWidget;

	UGameOverMenuWidget* GameOverWidget;

	USplashSceneWidget* SplashWidget;

	UPauseButtonWidget* PauseButton;

	URadianceGameInstance* GameInstance;

	void CreateWidgets();

};
