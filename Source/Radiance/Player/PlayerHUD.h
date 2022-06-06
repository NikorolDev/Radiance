#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

// Class references.
class UImage;
class URichTextBlock;
class UTextBlock;
class APlayerCharacter;
class AInventoryManager;
class ATooltipManager;
class UProgressBar;
class UWidgetAnimation;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			:	UPlayerHUD
// Author				:	Kurtis Watson
// Inherits				:	UUserWidget - Allows the class to be added to viewport as a widget.
// Purpose				:	Class to handle the HUD displayed on screen for the player.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

private:
	// Used to hold a reference to the player character.
	APlayerCharacter* m_pPlayerCharacter;

	// Holds the value of delta time for access within the class.
	float m_fDeltaTime;

	// Holds the value of the current dash cooldown.
	float m_fCurrentDashCooldown;

	// Used to handle the dash cooldown functionality.
	bool m_bDashCooldown;

	// To check if the tooltip animation is moving in. (Nikodem Hamrol)
	bool m_bIsTooltipMovingIn;

	// A pointer to tooltip manager for displaying the tooltip and setting them. (Nikodem Hamrol)
	ATooltipManager* m_pcTooltipManager;

	// The icon that is used to display along side the tooltip. (Nikodem Hamrol)
	UPROPERTY( meta = ( BindWidget ) )
		UImage*				TooltipIcon;

	// Animation to move the tooltip. (Nikodem Hamrol)
	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
		UWidgetAnimation*	MoveTooltip;

	// Animation to move the tooltip. (Nikodem Hamrol)
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* TakeDamageAnim;

	// Animation to move the tooltip. (Nikodem Hamrol)
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* CrosshairInflate;

	// Animation to move the tooltip. (Nikodem Hamrol)
	UPROPERTY(Transient, meta = (BindWidgetAnim))
		UWidgetAnimation* TimerAlert;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: AnimationFinished()
	// Author				: Nikodem Hamrol
	// Purpose				: A callback function that will be triggered when aniamtion is finished, which will set tooltips 
	//						, or display them
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void AnimationFinished();

protected:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	NativeConstruct
	// Author				:	UE4
	// Purpose				:	Native construct.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void NativeConstruct() override;

	// Used to hold a reference to the inventory manager.
	AInventoryManager* m_InventoryManager;

	// Timer handle to manage alet about inventory`s changes
	FTimerHandle m_DatabaseUpdatedAlertHandle;

	// Amount of time ti display the database alert
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float m_TimeToDisplayDatabaseAlert = 2.0f;

	// Reference the crosshair.
	UPROPERTY(meta = (BindWidget))
	UImage* Crosshair;

	// Reference the weapon charge text block.
	UPROPERTY(meta = (BindWidget))
		URichTextBlock* Tooltip;

	// Reference the 'Out of Charge' text block.
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NoChargeAlert;

	// Reference the 'Out of Charge' text block.
	UPROPERTY(meta = (BindWidget))
		URichTextBlock* InteractText;

	// Reference the 'Database Updated' text block.
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DatabaseUpdatedAlert;

	// Reference the weapon charge text block.
	UPROPERTY(meta = (BindWidget))
		URichTextBlock* LoopCount;

	// Reference the weapon charge text block.
	//UPROPERTY(meta = (BindWidget))
		//URichTextBlock* LoopTimer;

	// Reference the 'Dash Cooldown' progress bar.
	UPROPERTY(meta = (BindWidget))
	UProgressBar* DashCooldownBar;

	// Reference the 'Health Bar' progress bar.
	UPROPERTY(meta = (BindWidget))
		UProgressBar* HealthBar;

	// Reference the 'Gauntlet Charge' progress bar.
	UPROPERTY(meta = (BindWidget))
		UProgressBar* ChargeCountBar;

	// Reference the 'Gauntlet Charge' progress bar.
	UPROPERTY(meta = (BindWidget))
		UProgressBar* Battery;

	// Reference the weapon charge text block.
	UPROPERTY(meta = (BindWidget))
		URichTextBlock* BatteryPercentage;

public:
	~UPlayerHUD();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	NativeTick
	// Author				:	UE4
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Initialise
	// Author				:	Kurtis Watson
	// Purpose				:	To allow for variables etc. to be initialised, specific to this class.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Initialise(APlayerCharacter* pPlayerCharacter);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	ChangeCrosshairColor
	// Author				:	Kurtis Watson
	// Purpose				:	To change the color of the crosshair at runtime.
	// Parameters			:	fColor - The color to change the crosshair to.
	//-----------------------------------------------------------------------------------------------------------------------------
	void ChangeCrosshairColor(FColor fColor);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	UpdateHealth
	// Author				:	Kurtis Watson
	// Purpose				:	To change the value on screen of the players health.
	// Parameters			:	fChargeValue - The health to display on screen.
	//-----------------------------------------------------------------------------------------------------------------------------
	void UpdateHealth(float fCurrentHealth);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	UpdateCurrentCharge
	// Author				:	Kurtis Watson
	// Purpose				:	To change the value on screen of the charge of the gauntlet.
	// Parameters			:	fChargeValue - The charge to display on screen.
	//-----------------------------------------------------------------------------------------------------------------------------
	void UpdateCurrentCharge(float fCurrentCharge, float fMaxCharge);


	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	SetBarChargeVisibility
	// Author				:	Kurtis Watson
	// Purpose				:	To hide/show the charge bar of the gauntlet.
	// Parameters			:	eVisibility - The visibility to set the bar charge to.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetBarChargeVisibility(ESlateVisibility eVisibility);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	ShowNoChargeAlert
	// Author				:	Kurtis Watson
	// Purpose				:	To hide/show the 'No Charge' alert.
	// Parameters			:	eVisibility - Display or do not display.
	//-----------------------------------------------------------------------------------------------------------------------------
	void ShowNoChargeAlert(ESlateVisibility eVisibility);

	void SetInteractTextVisibility(ESlateVisibility eVisibility);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	SetTooltipProperties
	// Author				:	Kurtis Watson
	// Editor				:	Nikodem Hamrol
	// Purpose				:	Sets the properties of the tooltip.
	// Parameters			:	psTooltipText		- The text that will display  on the tooltip from the tooltip manager.
	//						,	pcTooltipTexture	- The texture icon that will appear along side the tooltip text.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetTooltipProperties( FString psTooltipText, UTexture2D* pcTooltipTexture );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	HideTooltip
	// Author				:	Kurtis Watson
	// Editors				:	Nikodem Hamrol
	// Purpose				:	Hide the tooltip.
	//-----------------------------------------------------------------------------------------------------------------------------
	void HideTooltip();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	DashCooldown
	// Author				:	Kurtis Watson
	// Purpose				:	Called to show the dash cooldown after the player dashes.
	//-----------------------------------------------------------------------------------------------------------------------------
	void DashCooldown();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	TakeDamage
	// Author				:	Kurtis Watson
	// Purpose				:	Called when the player is to take damage so the HUD element can be activated.
	//-----------------------------------------------------------------------------------------------------------------------------
	void TakeDamage();

	void OutOfTimerAlert();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	InflateCrosshair
	// Author				:	Kurtis Watson
	// Purpose				:	Called when the crosshair is to animate.
	//-----------------------------------------------------------------------------------------------------------------------------
	void InflateCrosshair();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	SetDashCooldownVisibility
	// Author				:	Kurtis Watson
	// Purpose				:	Hide/show dash cooldown bar.
	// Parameters			:	bIsDashCooldown - Allows the dash cooldown to be visible or not.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetDashCooldownVisibility(bool bIsDashCooldownVisible);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	SetLoopTimeRemaining
	// Author				:	Kurtis Watson
	// Purpose				:	To set the loop time remaining.
	// Parameters			:	fRemainingTime - Time to display.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetLoopTimeRemaining(float fRemainingTime, float fLoopMaxTime);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	SetLoopCount
	// Author				:	Kurtis Watson
	// Purpose				:	Show the loop count on screen.
	// Parameters			:	iCurrentLoop - Allows the dash cooldown to be visible or not.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetLoopCount(int32 iCurrentLoop);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	RefreshDatabaseUpdatedAlert
	// Author				:	Gaetano Trovato
	// Purpose				:	Delegate to received any message about inventory changes
	// Parameters			:	Name, Quantity
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
	void RefreshDatabaseUpdatedAlert(FName Name, int32 Quantity);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	GetChargeCountBar
	// Author				:	Kurtis Watson
	// Purpose				:	Allows other classes to get access to the charge count bar on the HUD.
	//-----------------------------------------------------------------------------------------------------------------------------
	UProgressBar* GetChargeCountBar();
};
