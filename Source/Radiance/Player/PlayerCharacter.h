// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

// Players states.
enum State {
	Gravity,
	Weapon
};

// Class references.
class AItem_Base;
class UPlayerAnimInstance;
class UPlayerHUD;
class AWeapon_Base;
class ATerminal;
class UAIPerceptionStimuliSourceComponent;
class UMaterialInterface;
class UMaterialInstanceDynamic;
class UNiagaraSystem;
class UNiagaraComponent;
class UInventoryWidget;
class UPauseMenuWidget;
class UCameraShakeBase;

// Messages.
DECLARE_DELEGATE(FPlayerDiedSignature);

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			:	APlayerCharacter
// Author				:	Kurtis Watson
// Inherits				:	ACharacter - Allows for reference to UE4 functions related to the character.
// Purpose				:	This class holds all functionality for the player character.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	bool m_bIsMovementLocked = false;
	
	bool m_bCanInteract = false;

	// Camera boom positioning the camera behind the character.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraArm;

	// Follow camera.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

	// Position where the gravity item will be held.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ItemHeldPosition;

	// Used to spawn a weapon in game.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AWeapon_Base> Weapon;	

	// Used to spawn a weapon in game.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menus", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UInventoryWidget> InventoryReference;

	// Used to spawn a weapon in game.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menus", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UPauseMenuWidget> PauseMenuReference;

	// The shake used when the player shoots.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UCameraShakeBase> ShootShake;

	// Crosshair colour (default).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface", meta = (AllowPrivateAccess = "true"))
		FColor DefaultCrosshair;

	// Crosshair colour (interact).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface", meta = (AllowPrivateAccess = "true"))
		FColor InteractCrosshair;

	// Used the create dynamic instances of all materials on the player so that they can be altered at runtime.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TArray<UMaterialInstanceDynamic*> DissolveMaterials;

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		:	APlayerCharacter
	// Author				:	Kurtis Watson
	//-----------------------------------------------------------------------------------------------------------------------------
	APlayerCharacter();

	// Look sensitivity rate.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float LookSensitivityMultiplier;

	// Speed when focused (aiming etc.).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties", meta = (DisplayName = "Health"))
		float fPlayerHealth;

	// Speed when focused (aiming etc.).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties", meta = (DisplayName = "Interaction Distance"))
		float fInteractDistance = 500;

	// Speed when focused (aiming etc.).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties", meta = (DisplayName = "Dissolve Duration"))
		float fDissolveDuration;

	// Speed when focused (aiming etc.).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties", meta = (DisplayName = "Camera Fade Duration"))
		float fCameraFadeDuration = 2;

	// Speed when focused (aiming etc.).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties", meta = (DisplayName = "Focus Walk Speed"))
		int iFocusWalkSpeed;

	// Cooldown before gauntlet can be used again.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties", meta = (DisplayName = "Gauntlet Cooldown"))
		int iGauntletCooldown;

	// Max distance before gauntlet can't be used.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties", meta = (DisplayName = "Gravity Gauntlet Distance"))
		int iGauntletDistance;

	// Max distance before gauntlet can't be used.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties", meta = (DisplayName = "Dash Cooldown"))
		float fDashCooldown = 5;

	// Max distance before gauntlet can't be used.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties", meta = (DisplayName = "Dash Distance"))
		int iDashDistance = 2500;

	// Min fall damage distance before taking damage.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties", meta = (DisplayName = "Min Distance Before Fall Damage"))
		int iMinFallDamageDistance = 800;

	// Max fall damage distance before death.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties", meta = (DisplayName = "Max Distance Before Fall Damage"))
		int iMaxFallDamageDistance = 1800;

	// Determines if player is shooting or not.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (DisplayName = "Is Player Shooting"))
		bool bIsShooting;

	// Reload animation.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montages", meta = (DisplayName = "Reload"))
		UAnimMontage* ReloadAnimation;

	// Shoot animation.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montages", meta = (DisplayName = "Shoot Animation"))
		UAnimMontage* ShootAnimation;

	// Shoot animation.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montages", meta = (DisplayName = "Hold Animation"))
		UAnimMontage* HoldAnimation;

	// Lift animation for when gauntlet is first used.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montages", meta = (DisplayName = "Lift Animation"))
		UAnimMontage* LiftAnimation;

	// Throw animation when gauntlet launches an object.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montages", meta = (DisplayName = "Throw Item"))
		UAnimMontage* ThrowAnimation;

	// Lift sound.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
		USoundWave* TakeDamageSFX;

	// Lift sound.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
		USoundWave* GauntletLift;

	// Pull sound.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
		USoundWave* GauntletPull;

	// Throw sound.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
		USoundWave* GauntletThrow;

	// Sound for when gauntlet is charged.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
		USoundWave* GauntletCharged;

	// Sound for when gauntlet is charged.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
		USoundWave* DashActive;

	// Sound for when gauntlet is charged.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
		USoundWave* DashCharging;

	// Reload sound.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
		USoundWave* ReloadSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Montages", meta = (DisplayName = "Reload"))
		UNiagaraSystem* DashSystem;

	// Delegate to send message when player dies
	FPlayerDiedSignature OnPlayerDied;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	GetCameraComponent
	// Author				:	Kurtis Watson
	// Purpose				:	Get the camera component attached to the player.
	//-----------------------------------------------------------------------------------------------------------------------------
	UCameraComponent* GetCameraComponent();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	GetHeldPosition
	// Author				:	Kurtis Watson
	// Purpose				:	Get the position to hover the held item at.
	//-----------------------------------------------------------------------------------------------------------------------------
	UStaticMeshComponent* GetHeldPosition();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	GetHUD
	// Author				:	Kurtis Watson
	// Purpose				:	Get a HUD reference.
	//-----------------------------------------------------------------------------------------------------------------------------
	UPlayerHUD* GetHUD();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	GetHitResult
	// Author				:	Kurtis Watson
	// Purpose				:	Get the hit result of the line trace when called.
	//-----------------------------------------------------------------------------------------------------------------------------
	FHitResult GetHitResult();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	GetWeaponHitResult
	// Author				:	Kurtis Watson
	// Purpose				:	Get the hit result of the weapon line trace when called.
	//-----------------------------------------------------------------------------------------------------------------------------
	FHitResult GetWeaponHitResult();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	SetRotationProperties
	// Author				:	Kurtis Watson
	// Purpose				:	To set the rotation properties of the third person camera at runtime.
	// Parameters			:	bUseControllerDesiredRotation - Use the controller desired rotation?
	//							bOrientRotationToMovement - Orient the players rotation to movement?
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetRotationProperties(bool bUseControllerDesiredRotation, bool bOrientRotationToMovement);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	GetIsDashing
	// Author				:	Kurtis Watson
	// Purpose				:	Called from the weapon class to play the shoot animation and set the correct properties.
	// Returns				:	Returns true or false dependant if the player is dashin or not.
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable)
	bool GetIsDashing();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Shoot
	// Author				:	Kurtis Watson
	// Purpose				:	Called from the weapon class to play the shoot animation and set the correct properties.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Shoot();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	ResetDash
	// Author				:	Kurtis Watson
	// Purpose				:	Resets the dash properties and clears the timers.
	//-----------------------------------------------------------------------------------------------------------------------------
	void ResetDash();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Die
	// Author				:	Kurtis Watson
	// Purpose				:	Called when the player dies.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Die();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Respawn
	// Author				:	Kurtis Watson
	// Purpose				:	Called when the player is required to respawn.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Respawn();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	LoopReset
	// Author				:	Kurtis Watson
	// Purpose				:	Called when the player is required to respawn when the loop timer runs out.
	//-----------------------------------------------------------------------------------------------------------------------------
	void LoopReset();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	LockPlayerMovement
	// Author				:	Kurtis Watson
	// Purpose				:	Called when the player movement and hud is to be enabled/disabled.
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable)
		void LockPlayerMovement(bool bLockMovement);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	TakeDamage
	// Author				:	Kurtis Watson
	// Purpose				:	Called to have the player take damage.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	DropItem
	// Author				:	Kurtis Watson
	// Purpose				:	Called to drop the item if one is held.
	//-----------------------------------------------------------------------------------------------------------------------------
	void DropItem();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	TogglePauseMenu
	// Author				:	Kurtis Watson
	// Purpose				:	Shows pause menu when ESC is pressed.
	//-----------------------------------------------------------------------------------------------------------------------------
	void EnablePauseMenu();

	void DisablePauseMenu();

	bool GetIsDead();
	
	UFUNCTION(BlueprintCallable)
	bool GetLockedState();

protected:
	// Holds the linetrace hit results.
	FHitResult		m_Hit;
	FHitResult		m_WeaponHit;

	// Stores the start and end position of line trace.
	FVector			m_v3StartPosition;
	FVector			m_v3EndPosition;
	FVector			m_v3SpawnPosition;

	// Holds the players current state.
	State			m_eCurrentState;

	// Timers.
	FTimerHandle	m_GameTimer;
	FTimerHandle	m_ResetRotationTimer;
	FTimerHandle	m_DashStopTimer;
	FTimerHandle	m_DashTimeout;
	FTimerHandle	m_DeathTimer;
	FTimerHandle	m_SwitchAnimationTimer;
	FTimerHandle	m_LandedTimer;

	// Reference the games HUD widget.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (DisplayName = "HUD Widget Reference"))
		TSubclassOf<UUserWidget> m_pHUDWidgetReference;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Landed
	// Author				:	Kurtis Watson
	// Purpose				:	Called when the player lands on the ground.
	// Parameters			:	Hit - The hit object.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void Landed(const FHitResult& Hit) override;

private:
#pragma region Variables
	// Speed of player.
	float					m_fDeltaTime;

	FRotator				m_rPlayerStartRotation;
	FRotator				m_rCameraStartingRotation;

	// Holds the default walk speed.
	int						m_iDefaultWalkSpeed;

	// Holds the initial health of the player set in engine.
	float					m_fPlayerMaxHealth;
	float					m_fCurrentDissolveCount;

	// Check for if the item is in range.
	bool					m_bItemInRange;
	bool					m_bDissolve;
	bool					m_bDissolveIn;
	bool					m_bPauseToggled;


	// Player state bools and checks.
	bool					m_bIsShooting;
	bool				    m_bIsDashing;
	bool					m_bCanDash;
	bool					m_bCanGrab;
	bool					m_bCanShoot;
	bool					m_bInventoryOpen;

	// Reference to the HUD.
	UPlayerHUD* m_pHUD;

	// Used to reference the item held base class.
	AItem_Base* m_pItemInRange;
	AItem_Base* m_pItemHeld;

	// Used to reference the current weapons base class.
	AWeapon_Base* m_pWeapon;

	// Used to handle the players animation instances.
	UPlayerAnimInstance* m_pAnimInstance;

	// Used to allow the enemies to add the player to their perception for detection.
	UAIPerceptionStimuliSourceComponent* m_pcStimulusSource;

	// Dash particle reference.
	UNiagaraComponent* m_pcDashParticles;

	// Inventory instance.
	UInventoryWidget* InventoryInstance;

	// Pause Menu instance.
	UPauseMenuWidget* PauseMenuInstance;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	SetupStimulusSource
	// Author				:	Kurtis Watson
	// Purpose				:	Called at begin in order to allow the player to be detected by the enemies.
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void SetupStimulusSource();

#pragma endregion

#pragma region Overrides

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	BeginPlay
	// Author				:	UE4
	// Purpose				:	Called when the game is first loaded.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Tick
	// Author				:	UE4
	// Purpose				:	Called each frame (update).
	// Parameters			:	DeltaTime - Calculates the time different between previous and current frame.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void Tick(float DeltaTime) override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	SetupPlayerInputComponent
	// Author				:	Kurtis Watson
	// Purpose				:	PlayerInputComponent - Used to set up key bindings and actions.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma endregion

#pragma region Input Functions
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	LeftClickPressed
	// Author				:	Kurtis Watson
	// Purpose				:	Called when left mouse button is pressed.
	//-----------------------------------------------------------------------------------------------------------------------------
	void LeftClickPressed();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	LeftClickReleased
	// Author				:	Kurtis Watson
	// Purpose				:	Called when left mouse button is released.
	//-----------------------------------------------------------------------------------------------------------------------------
	void LeftClickReleased();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	RightClickPressed
	// Author				:	Kurtis Watson
	// Purpose				:	Called when right mouse button is pressed.
	//-----------------------------------------------------------------------------------------------------------------------------
	void RightClickPressed();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	RightClickReleased
	// Author				:	Kurtis Watson
	// Purpose				:	Called when right mouse button is released.
	//-----------------------------------------------------------------------------------------------------------------------------
	void RightClickReleased();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	MoveForward
	// Author				:	Kurtis Watson
	// Purpose				:	Move player forward/backward dependant on the parameter value.
	// Parameters			:	Value - Axis value.
	//-----------------------------------------------------------------------------------------------------------------------------
	void MoveForward(float Value);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	MoveRight
	// Author				:	Kurtis Watson
	// Purpose				:	Move player left/right dependant on the parameter value.
	// Parameters			:	Value - Axis value.
	//-----------------------------------------------------------------------------------------------------------------------------
	void MoveRight(float Value);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Interact
	// Author				:	Kurtis Watson
	// Purpose				:	Called when the player presses the interact button 'E' while looking at an actor in scene.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Interact();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Inventory
	// Author				:	Kurtis Watson
	// Purpose				:	
	//-----------------------------------------------------------------------------------------------------------------------------
	void Inventory();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	OpenInventory
	// Author				:	Kurtis Watson
	// Purpose				:	
	//-----------------------------------------------------------------------------------------------------------------------------
	void OpenInventory();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	CloseInventory
	// Author				:	Kurtis Watson
	// Purpose				:	
	//-----------------------------------------------------------------------------------------------------------------------------
	void CloseInventory();

#pragma endregion

#pragma region Input Responses

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	ResetGrab
	// Author				:	Kurtis Watson
	// Purpose				:	To reset the properties of the grab gauntlet.
	//-----------------------------------------------------------------------------------------------------------------------------
	void ResetGrab();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	ThrowItem
	// Author				:	Kurtis Watson
	// Purpose				:	To throw the item if one is held and reset all variables where necessary.
	//-----------------------------------------------------------------------------------------------------------------------------
	void ThrowItem();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	GrabItem
	// Author				:	Kurtis Watson
	// Purpose				:	Called to pull the item towards the player.
	//-----------------------------------------------------------------------------------------------------------------------------
	void GrabItem();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	StopShooting
	// Author				:	Kurtis Watson
	// Purpose				:	Stop shooting.
	//-----------------------------------------------------------------------------------------------------------------------------
	void StopShooting();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	BeginDash
	// Author				:	Kurtis Watson
	// Purpose				:	To reset the players dash.
	//-----------------------------------------------------------------------------------------------------------------------------
	void BeginDash();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	StopDash
	// Author				:	Kurtis Watson
	// Purpose				:	To reset the players dash.
	//-----------------------------------------------------------------------------------------------------------------------------
	void StopDash();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	ResetRotation
	// Author				:	Kurtis Watson
	// Purpose				:	To reset the players rotation.
	//-----------------------------------------------------------------------------------------------------------------------------
	void ResetRotation();

#pragma endregion

#pragma region Tools

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	LineTrace
	// Author				:	Kurtis Watson
	// Purpose				:	Called every frame to determine what the player is looking at.
	//-----------------------------------------------------------------------------------------------------------------------------
	void LineTrace();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	LineTraceChannelHandler
	// Author				:	Kurtis Watson
	// Purpose				:	Determines the line trace channel to use based on the players current state.
	//-----------------------------------------------------------------------------------------------------------------------------
	void LineTraceChannelHandler();

#pragma endregion

#pragma region Check Functions

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	CheckObjectType
	// Author				:	Kurtis Watson
	// Purpose				:	Checks to see if the item the player is looking at is an 'Item_Base' class.
	//-----------------------------------------------------------------------------------------------------------------------------
	bool CheckObjectType();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	CheckDistance
	// Author				:	Kurtis Watson
	// Purpose				:	Checks the distance of the item the player is looking at from their current position.
	//-----------------------------------------------------------------------------------------------------------------------------
	bool CheckDistance();

#pragma endregion
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	MapRangedClamped
	// Author				:	Kurtis Watson
	// Purpose				:	Takes in a value and returns a new value dependant on the parameters passed through (used for
	//							clamping).
	// Parameters			:	fValue - Value to check against.
	//							fInRangeA - The lowest the value can be.
	//							fInRangeB - The highest the value can be.
	//							fOutRangeA - The first output range based on the percentage of fInRange A/B calculations.
	//							fOutRangeB - The second output range based on the percentage of fInRange A/B calculations.
	//-----------------------------------------------------------------------------------------------------------------------------
	float MapRangedClamped(float fValue, float fInRangeA, float fInRangeB, float fOutRangeA, float fOutRangeB);

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	DissolveHandler
	// Author				:	Kurtis Watson
	// Purpose				:	Handles the player dissolve material.
	//-----------------------------------------------------------------------------------------------------------------------------
	void DissolveHandler();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	SwitchGauntletAnimation
	// Author				:	Kurtis Watson
	// Purpose				:	Switches the gauntlet animation based on the current state.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SwitchGauntletAnimation();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	SwitchLandedAnimation
	// Author				:	Kurtis Watson
	// Purpose				:	Resets the landing animations.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SwitchLandedAnimation();
};

