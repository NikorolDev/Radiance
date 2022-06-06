// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Radiance/Items/Interactable.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "PlayerAnimInstance.h"
#include "Math/UnrealMathUtility.h"
#include "Radiance/Items/Item_Base.h"
#include "Radiance/Items/Item_Throwable.h"
#include "PlayerHUD.h"
#include "Sound/SoundWave.h"
#include "Weapon_Base.h"
#include "Radiance/Puzzle/Terminal.h"
#include "Radiance/LoopManager.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMathLibrary.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include "Radiance/Inventory/InventoryWidget.h"
#include "Radiance/Menus/PauseMenuWidget.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LookSensitivityMultiplier = 0.6f;

	// Set size for collision capsule.
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement.
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision).
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller.
	CameraArm->SetRelativeLocation(FVector(0, 70, 90));
	CameraArm->bEnableCameraLag = true;
	CameraArm->CameraLagSpeed = 10.0f;

	// Create a camera.
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation.
	Camera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm.

	// Reference the position where the objects will 'hover' when held.
	ItemHeldPosition = CreateDefaultSubobject<UStaticMeshComponent>("Held Position");
	ItemHeldPosition->SetupAttachment(CameraArm);
	ItemHeldPosition->SetVisibility(false);

	// Set the default properties of the player on start-up.
	m_bCanGrab = true;
	m_bCanDash = true;
	bIsShooting = false;
	m_pItemHeld = nullptr;
	m_eCurrentState = State::Weapon;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	m_iDefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;

	// Set starting rotation properties.
	SetRotationProperties(false, true);
}

void APlayerCharacter::SetupStimulusSource()
{
	m_pcStimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus Source"));
	m_pcStimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
	m_pcStimulusSource->RegisterWithPerceptionSystem();
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Stores the player initial health.
	m_fPlayerMaxHealth = fPlayerHealth;

	m_bDissolve = true;
	m_bDissolveIn = true;
	m_bCanShoot = true;
	m_bInventoryOpen = false;

	FRotator DashRotation = UKismetMathLibrary::MakeRotFromX(GetActorForwardVector());
	m_pcDashParticles = UNiagaraFunctionLibrary::SpawnSystemAttached(DashSystem, GetCapsuleComponent(), FName(), GetActorLocation(), DashRotation, FVector(1, 1, 1), EAttachLocation::KeepWorldPosition, true, ENCPoolMethod::None, false, true);

	// Stores the players spawn position.
	m_v3SpawnPosition = GetActorLocation();

	m_rPlayerStartRotation = GetCapsuleComponent()->GetComponentRotation();
	m_rCameraStartingRotation = GetController()->GetControlRotation();

	// Reference the animation instance attached to the mesh.
	m_pAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	// Create a widget and initialise the hud.
	m_pHUD = CreateWidget<UPlayerHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0), m_pHUDWidgetReference);
	m_pHUD->Initialise(this);
	m_pHUD->AddToViewport();
	m_pHUD->UpdateHealth(fPlayerHealth / m_fPlayerMaxHealth);
	m_pHUD->ChangeCrosshairColor(DefaultCrosshair);

	// Reference and initialise the weapon.
	m_pWeapon = GetWorld()->SpawnActor<AWeapon_Base>(Weapon);
	m_pWeapon->Initialise(this);
	InventoryInstance = CreateWidget<UInventoryWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), InventoryReference);
	InventoryInstance->AddToViewport();
	CloseInventory();

	PauseMenuInstance = CreateWidget<UPauseMenuWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), PauseMenuReference);
	PauseMenuInstance->SetPlayerCharacter(this);
	PauseMenuInstance->AddToViewport();
	PauseMenuInstance->SetVisibility(ESlateVisibility::Hidden);

	for (int i = 0; i < GetMesh()->GetMaterials().Num(); i++)
	{
		UMaterialInterface* Material = GetMesh()->GetMaterial(i);
		DissolveMaterials.Add(GetMesh()->CreateDynamicMaterialInstance(i, Material));
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fDeltaTime = DeltaTime;

	// Draw a line trace along camera's forward vector.
	LineTrace();

	// Checks the distance between the player and surrounding objects.
	CheckDistance();

	DissolveHandler();

	m_pAnimInstance->isFalling = GetMovementComponent()->IsFalling();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &APlayerCharacter::BeginDash);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APlayerCharacter::EnablePauseMenu);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);

	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &APlayerCharacter::Inventory).bExecuteWhenPaused = true;

	PlayerInputComponent->BindAction("LeftClick", IE_Pressed, this, &APlayerCharacter::LeftClickPressed);
	PlayerInputComponent->BindAction("LeftClick", IE_Released, this, &APlayerCharacter::LeftClickReleased);

	PlayerInputComponent->BindAction("RightClick", IE_Pressed, this, &APlayerCharacter::RightClickPressed);
	PlayerInputComponent->BindAction("RightClick", IE_Released, this, &APlayerCharacter::RightClickReleased);
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (fPlayerHealth != 0)
	{
		// Substract Health 
		fPlayerHealth -= DamageAmount;

		m_pHUD->TakeDamage();

		// Update the HUD as the player has taken damage.
		m_pHUD->UpdateHealth(fPlayerHealth / m_fPlayerMaxHealth);

		// Play charged audio sound to indicate to player that they have taken damage.
		UGameplayStatics::PlaySound2D(GetWorld(), TakeDamageSFX, 1);

		// Player death check. >
		if (fPlayerHealth <= 0)
		{
			// > Call the 'Die' function that handles the death animation and respawn functionality.
			Die();
		}

	}
	// Returns the player health.
	return fPlayerHealth;
}

void APlayerCharacter::Landed(const FHitResult& Hit)
{
	// Gets the speed at which the player was falling on collision with the floor.
	float fSpeed = FMath::Abs(GetVelocity().Z);

	// The normalised value the min and max fall damage as a value of 0 to 1.
	float fDamage = UKismetMathLibrary::NormalizeToRange(fSpeed, iMinFallDamageDistance, iMaxFallDamageDistance);
	float fClampedDamage = UKismetMathLibrary::FClamp(fDamage, 0, 1);

	// Apply the damage to the player (*100) as the health is 100 and not 1.
	UGameplayStatics::ApplyDamage(this, fClampedDamage * 100, GetController(), this, UDamageType::StaticClass());

	m_pAnimInstance->hasLanded = true;
	GetWorldTimerManager().SetTimer(m_LandedTimer, this, &APlayerCharacter::SwitchLandedAnimation, 0.4f, false);
}

void APlayerCharacter::Shoot()
{
	// Change the rotation properties while the player is shooting.
	SetRotationProperties(true, false);

	// Allows the animation instance to recognise the player is shooting.
	m_pAnimInstance->IsShooting = true;

	m_pHUD->InflateCrosshair();

	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(ShootShake, 1.0f);

	// Play the shooting animation.
	PlayAnimMontage(ShootAnimation);
}

void APlayerCharacter::StopShooting()
{
	// Allow the system to recognise when the player has stopped shooting.
	bIsShooting = false;

	// Reset animation instance.
	m_pAnimInstance->IsShooting = false;

	GetWorldTimerManager().SetTimer(m_ResetRotationTimer, this, &APlayerCharacter::ResetRotation, 0.5f, false);

	// Stop the weapon from firing.
	m_pWeapon->EndShoot();
}

void APlayerCharacter::GrabItem()
{
	// Check that the line trace has hit an item object.
	if (m_bItemInRange && m_bCanGrab && CheckObjectType())
	{
		PlayAnimMontage(LiftAnimation);

		// Play charged audio sound to indicate to player that the gauntlet is charged.
		UGameplayStatics::PlaySound2D(GetWorld(), GauntletPull, 1);

		// Cast to the hit object.
		m_pItemHeld = Cast<AItem_Base>(m_Hit.GetActor());
		m_pItemHeld->SetTarget(this);

		// Stop the player from being able to grab another item.
		m_bCanGrab = false;
		m_eCurrentState = State::Gravity;

		// Hide the weapon.
		m_pWeapon->SetActorHiddenInGame(true);

		// Rotate with camera.
		bUseControllerRotationYaw = true;

		// Trigger the gravity gauntlet state and play animation.
		m_pAnimInstance->isGravityState = true;

		m_pAnimInstance->IsShooting = true;

		GetWorldTimerManager().SetTimer(m_SwitchAnimationTimer, this, &APlayerCharacter::SwitchGauntletAnimation, LiftAnimation->GetPlayLength(), false);
	}
}

void APlayerCharacter::ThrowItem()
{
	// Checks if an item is held as well as it being a throwable object.
	if (m_pItemHeld && m_pItemHeld->IsA<AItem_Throwable>())
	{
		// Cast to the object held so that is can be thrown.
		AItem_Throwable* Throwable = Cast<AItem_Throwable>(m_pItemHeld);
		Throwable->ItemThrown(m_Hit.ImpactPoint);

		// Play charged audio sound to indicate to player that the gauntlet is charged.
		UGameplayStatics::PlaySound2D(GetWorld(), GauntletThrow, 1);

		// Change the players movement speed back to the original value.
		GetCharacterMovement()->MaxWalkSpeed = m_iDefaultWalkSpeed;

		// Reset the held item.
		m_pItemHeld = nullptr;

		// Rotate around the player, rather than the player rotate with camera.
		bUseControllerRotationYaw = false;

		// Reset anim instance bools.
		m_pAnimInstance->isGravityState = false;
		m_pAnimInstance->IsShooting = false;

		// Show weapon again.
		m_pWeapon->SetActorHiddenInGame(false);

		GetWorldTimerManager().ClearTimer(m_SwitchAnimationTimer);

		// Play the montage before resetting rotation and animation state back to weapon state.
		PlayAnimMontage(ThrowAnimation);

		// Reset the rotation properties.
		SetRotationProperties(false, true);

		// Calls the 'ResetGrab' function after 'x' seconds as the item has been thrown.
		GetWorldTimerManager().SetTimer(m_GameTimer, this, &APlayerCharacter::ResetGrab, iGauntletCooldown, false);

		m_eCurrentState = State::Weapon;
	}
}

void APlayerCharacter::DropItem()
{
	// Check to make sure the item has not yet been thrown.
	if (m_pItemHeld && !m_pItemHeld->GetIsThrown())
	{
		GetWorldTimerManager().ClearTimer(m_SwitchAnimationTimer);

		StopAnimMontage(HoldAnimation);

		// Change players current state.
		m_eCurrentState = State::Weapon;

		// Reset the items values as it was not thrown.
		m_pItemHeld->Dropped();

		m_pAnimInstance->IsShooting = false;

		// Remove the pointer.
		m_pItemHeld = nullptr;

		// Allow for rotation around the player as they are no longer 'focused'
		bUseControllerRotationYaw = false;

		// Reset anim state.
		m_pAnimInstance->IsShooting = false;
		m_pAnimInstance->isGravityState = false;

		// Show the weapon again.
		m_pWeapon->SetActorHiddenInGame(false);

		// Timer before player can use the gravity gauntlet again.
		GetWorldTimerManager().SetTimer(m_GameTimer, this, &APlayerCharacter::ResetGrab, iGauntletCooldown, false);
	}
}

bool APlayerCharacter::GetIsDead()
{
	return m_pAnimInstance->isDead;
}

void APlayerCharacter::ResetGrab()
{
	// Allow the player to grab again and play a sound to indicate the activation.
	m_bCanGrab = true;

	// Play charged audio sound to indicate to player that the gauntlet is charged.
	UGameplayStatics::PlaySound2D(GetWorld(), GauntletCharged, 1);

	// Reset the timer.
	GetWorldTimerManager().ClearTimer(m_GameTimer);
}

void APlayerCharacter::BeginDash()
{
	if (m_bCanDash && !m_bIsMovementLocked)
	{
		m_bCanShoot = false;
		// Change the speed of the players max walk speed to replicate a 'dash'.
		GetCharacterMovement()->MaxWalkSpeed = 100000;
		GetCharacterMovement()->MaxAcceleration = 100000;
		GetCapsuleComponent()->SetEnableGravity(false);

		// Stop the player from dashing and allow the system to recognise the player is dashing.
		m_bCanDash = false;
		m_bIsDashing = true;

		// Activate the dash particles.
		//DashParticles->Activate();

		// Play charged audio sound to indicate to player that the gauntlet is charged.
		UGameplayStatics::PlaySound2D(GetWorld(), DashActive, 1);

		// Play charged audio sound to indicate to player that the gauntlet is charged.
		UGameplayStatics::PlaySound2D(GetWorld(), DashCharging, 1);

		// Timer before player can use the gravity gauntlet again.
		GetWorldTimerManager().SetTimer(m_DashStopTimer, this, &APlayerCharacter::StopDash, 0.1f, false);
	}
}

void APlayerCharacter::StopDash()
{
	m_bCanShoot = true;

	// Reset the players max walk speed and acceleration.
	GetCharacterMovement()->MaxWalkSpeed = 600;
	GetCharacterMovement()->MaxAcceleration = 2048;
	GetCapsuleComponent()->SetEnableGravity(false);
	GetCharacterMovement()->StopMovementImmediately();

	//DashParticles->Deactivate();

	m_bIsDashing = false;
	m_pHUD->SetDashCooldownVisibility(true);
	GetWorldTimerManager().ClearTimer(m_DashStopTimer);
}

void APlayerCharacter::ResetRotation()
{
	// Reset rotation properties.
	SetRotationProperties(false, true);
	GetWorldTimerManager().ClearTimer(m_ResetRotationTimer);
}

void APlayerCharacter::ResetDash()
{
	// Allow the player to dash again.
	m_bCanDash = true;

	// Clear the dash timer, ready for the next call.
	GetWorldTimerManager().ClearTimer(m_DashTimeout);
}

void APlayerCharacter::Die()
{
	// Send message that player died
	OnPlayerDied.Execute();

	// Play the death animation.
	m_pAnimInstance->isDead = true;

	DropItem();

	// Respawn the player after 'x' seconds.
	GetWorldTimerManager().SetTimer(m_DeathTimer, this, &APlayerCharacter::Respawn, 5, false);
}

void APlayerCharacter::Respawn()
{
	// Reset the players health and updates it on the UI.
	fPlayerHealth = m_fPlayerMaxHealth;
	m_pHUD->UpdateHealth(fPlayerHealth / m_fPlayerMaxHealth);

	// Stops the death animation playing.
	m_pAnimInstance->isDead = false;

	// Sets the position of the player.
	SetActorLocation(m_v3SpawnPosition);

	// Clears the death timer.
	GetWorldTimerManager().ClearTimer(m_DeathTimer);

	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(1, 0, fCameraFadeDuration, FColor::Black, false, true);

	GetCapsuleComponent()->SetRelativeRotation(m_rPlayerStartRotation);
	GetController()->SetControlRotation(m_rCameraStartingRotation);

	m_bDissolve = true;
	m_bDissolveIn = true;
}

void APlayerCharacter::LoopReset()
{
	DropItem();

	if (m_pAnimInstance->Montage_IsPlaying(HoldAnimation))
	{
		m_pAnimInstance->StopAllMontages(2);
	}

	m_bDissolveIn = false;
	m_bDissolve = true;

	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(0, 1, fCameraFadeDuration, FColor::Black, false, true);

	// Respawn the player after 'x' seconds.
	GetWorldTimerManager().SetTimer(m_DeathTimer, this, &APlayerCharacter::Respawn, 2.5f, false);
}

void APlayerCharacter::LockPlayerMovement(bool bLockMovement)
{
	m_bIsMovementLocked = bLockMovement;

	//if (bLockMovement)
	//{
	//	m_pHUD->RemoveFromViewport();
	//	DisableInput(GetWorld()->GetFirstPlayerController());
	//}
	//else
	//{
	//	m_pHUD->AddToViewport();
	//	EnableInput(GetWorld()->GetFirstPlayerController());
	//	//GetWorld()->GetFirstPlayerController()->SetInputMode( FInputModeGameAndUI() );
	//}
}

void APlayerCharacter::EnablePauseMenu()
{
	if (!PauseMenuInstance->IsVisible())
	{
		PauseMenuInstance->SetVisibility(ESlateVisibility::Visible);
		UWidgetBlueprintLibrary::SetInputMode_GameAndUI(GetWorld()->GetFirstPlayerController(), PauseMenuInstance);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	}
}

void APlayerCharacter::DisablePauseMenu()
{
	if (PauseMenuInstance->IsVisible())
	{
		PauseMenuInstance->SetVisibility(ESlateVisibility::Hidden);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
		m_bIsMovementLocked = false;
	}
}

void APlayerCharacter::LeftClickPressed()
{
	// Makes sure the player is not in death state.
	if (!m_pAnimInstance->isDead && !m_bIsMovementLocked)
	{
		m_bIsShooting = true;
		// Check the current state.
		switch (m_eCurrentState)
		{
		case State::Gravity:
			// Throw the item held.
			ThrowItem();
			break;
		case State::Weapon:
			// Shoot a projectile.
			if (m_bCanShoot)
			{
				m_pWeapon->BeginShoot();
			}
			break;
		}
	}
}

void APlayerCharacter::LeftClickReleased()
{
	if (!m_bIsMovementLocked)
	{
		// Stop the player from shooting.
		m_bIsShooting = false;

		// Check the current state.
		switch (m_eCurrentState)
		{
		case State::Weapon:
			StopShooting();
			break;
		}
	}

}

void APlayerCharacter::RightClickPressed()
{
	// Makes sure the player isn't dead.
	if (!m_pAnimInstance->isDead && !m_bIsMovementLocked)
	{
		// Pull an item towards the grab location.
		if (m_pItemHeld)
		{
			DropItem();
		}
		else
		{
			GrabItem();
		}
	}
}

void APlayerCharacter::RightClickReleased()
{
	// Drop the Item held.
	//DropItem();
}

void APlayerCharacter::MoveForward(float Value)
{
	// Check that there is a controller valid.
	if (!m_bIsMovementLocked && (Controller != nullptr) && (Value != 0.0f) && !m_pAnimInstance->isDead)
	{
		// Find out which way is forward.
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector.
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Move player.
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	// Check that there is a controller valid.
	if (!m_bIsMovementLocked && (Controller != nullptr) && (Value != 0.0f) && !m_pAnimInstance->isDead)
	{
		// Find out which way is right.
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get right vector.
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Move player.
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::Interact()
{
	if (!m_bIsMovementLocked && m_bCanInteract)
	{
		IInteractable* Interactable = Cast<IInteractable>(m_Hit.Actor);
		if (Interactable)
		{
			Interactable->Execute_OnInteract(m_Hit.Actor.Get(), this);
		}
	}
}

void APlayerCharacter::Inventory()
{
	if (!m_bIsMovementLocked)
	{
		m_bInventoryOpen = !m_bInventoryOpen;

		UGameplayStatics::SetGamePaused(GetWorld(), m_bInventoryOpen);

		if (m_bInventoryOpen)
		{
			OpenInventory();
		}
		else
		{
			CloseInventory();
		}
	}

}

void APlayerCharacter::OpenInventory()
{
	InventoryInstance->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	// Calling the blueprint function to set input mode to game and UI (maybe fix with the internal c++ version later)
	UWidgetBlueprintLibrary::SetInputMode_GameAndUI( GetWorld()->GetFirstPlayerController(), InventoryInstance );

}

void APlayerCharacter::CloseInventory()
{
	InventoryInstance->SetVisibility(ESlateVisibility::Hidden);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly( GetWorld()->GetFirstPlayerController());
}

void APlayerCharacter::LineTrace()
{
	// Max distance (rooms are max 1500) so no need for a public variable.
	float TraceDistance = 10000;

	// Trace positions.
	m_v3StartPosition = Camera->GetComponentLocation();
	m_v3EndPosition = m_v3StartPosition + (Camera->GetForwardVector() * TraceDistance);

	LineTraceChannelHandler();
}

void APlayerCharacter::LineTraceChannelHandler()
{
	GetWorld()->LineTraceSingleByChannel(m_WeaponHit, m_v3StartPosition, m_v3EndPosition, ECollisionChannel::ECC_Camera);


	IInteractable* Interactable = Cast<IInteractable>(m_WeaponHit.Actor);
	if (Interactable)
	{
	// Get a Vector of two positions.
	FVector Positions = GetActorLocation() - m_WeaponHit.Actor->GetActorLocation();

	float Distance = Positions.Size();
		if (Distance < fInteractDistance)
		{
			m_pHUD->SetInteractTextVisibility(ESlateVisibility::Visible);
			m_bCanInteract = true;
		}
	}
	else
	{
		m_pHUD->SetInteractTextVisibility(ESlateVisibility::Hidden);
		m_bCanInteract = false;
		Interactable = nullptr;
	}

	// Add the line trace to the channel.
	if (m_pItemHeld)
	{
		// Allows for detection of other item colliders.
		GetWorld()->LineTraceSingleByChannel(m_Hit, m_v3StartPosition, m_v3EndPosition, ECollisionChannel::ECC_Camera);
	}
	else
	{
		// Ignores the detection of other item colliders.
		GetWorld()->LineTraceSingleByChannel(m_Hit, m_v3StartPosition, m_v3EndPosition, ECollisionChannel::ECC_GameTraceChannel1);
	}
}

void APlayerCharacter::SetRotationProperties(bool bUseControllerDesiredRotation, bool bOrientRotationToMovement)
{
	// Set the rotation properties. 
	GetCharacterMovement()->bUseControllerDesiredRotation = bUseControllerDesiredRotation; // Rotate with controller.
	GetCharacterMovement()->bOrientRotationToMovement = bOrientRotationToMovement;	// Rotate with movement.
}

float APlayerCharacter::MapRangedClamped(float fValue, float fInRangeA, float fInRangeB, float fOutRangeA, float fOutRangeB)
{
	// Used to reassign one range of numbers to another based on the input value.
	// Example:
	// If value is 25, in range 0, out range 100.
	// (25 - 0) / (0 - 100) = 25 / -100 = -0.25.
	// This means that it will return clamp value outRangeA.

	// If a out A is equal to out B, return either as they are the same value.
	if (fOutRangeA == fOutRangeB)
	{
		return fOutRangeA;
	}

	// Calculates the clamp value to apply to the object dependant on the mass.
	float inPercentage = (fValue - fInRangeA) / (fInRangeB - fInRangeA);

	// Return if the value is less than 0.
	if (inPercentage < 0.0f)
	{
		return fOutRangeA;
	}

	// Return if the value is greater than 0.
	if (inPercentage > 1.0f)
	{
		return fOutRangeB;
	}

	return fOutRangeA + inPercentage * (fOutRangeB - fOutRangeA);
}

void APlayerCharacter::DissolveHandler()
{
	if (m_bDissolve)
	{
		if (m_fCurrentDissolveCount < fDissolveDuration)
		{
			float iDissolveValue;

			if (m_bDissolveIn)
			{
				iDissolveValue = FMath::Lerp(0.f, 1.f, m_fCurrentDissolveCount / fDissolveDuration);
			}
			else
			{
				iDissolveValue = FMath::Lerp(1.f, 0.f, m_fCurrentDissolveCount / fDissolveDuration);
			}
			for (UMaterialInstanceDynamic* i : DissolveMaterials)
			{
				i->SetScalarParameterValue("Appearance", iDissolveValue);
			}
			m_fCurrentDissolveCount += m_fDeltaTime;
		}
		else
		{
			m_bDissolve = false;
			m_fCurrentDissolveCount = 0;
		}
	}
}

void APlayerCharacter::SwitchGauntletAnimation()
{
	PlayAnimMontage(HoldAnimation);
	GetWorldTimerManager().ClearTimer(m_SwitchAnimationTimer);
}

void APlayerCharacter::SwitchLandedAnimation()
{
	m_pAnimInstance->hasLanded = false;
	GetWorldTimerManager().ClearTimer(m_LandedTimer);
}

bool APlayerCharacter::CheckObjectType()
{
	// Check that the object hit is an Item class.
	if (m_Hit.Actor->IsA<AItem_Base>())
	{
		return true;
	}
	return false;
}

bool APlayerCharacter::CheckDistance()
{
	if (m_Hit.bBlockingHit)
	{
		// Get a Vector of two positions.
		FVector Positions = GetActorLocation() - m_Hit.GetActor()->GetActorLocation();

		// Size is used to retrieve the distance between two points.
		float Distance = Positions.Size();

		//	Is the player close enough to use gravity gauntlet.
		if (Distance < iGauntletDistance && CheckObjectType())
		{
			// Allow for pickup.
			m_bItemInRange = true;

			if (!m_pItemInRange)
			{
				m_pItemInRange = Cast<AItem_Base>(m_Hit.GetActor());
				m_pItemInRange->GetMesh()->SetRenderCustomDepth(true);
			}
			else if (m_pItemInRange != m_Hit.GetActor())
			{

				m_pItemInRange->GetMesh()->SetRenderCustomDepth(false);
				m_pItemInRange = Cast<AItem_Base>(m_Hit.GetActor());
				m_pItemInRange->GetMesh()->SetRenderCustomDepth(true);
			}

			// Change crosshair color.
			m_pHUD->ChangeCrosshairColor(InteractCrosshair);
			return true;
		}
		else
		{
			// Don't allow for pickup.
			m_bItemInRange = false;

			if (m_pItemInRange)
			{
				m_pItemInRange->GetMesh()->SetRenderCustomDepth(false);
				m_pItemInRange = nullptr;
			}

			// Change crosshair color.
			m_pHUD->ChangeCrosshairColor(DefaultCrosshair);
		}
	}
	return false;
}

UCameraComponent* APlayerCharacter::GetCameraComponent()
{
	// Get the camera attached to the player.
	return Camera;
}

UStaticMeshComponent* APlayerCharacter::GetHeldPosition()
{
	// Get the position of the hold item position.
	return ItemHeldPosition;
}

UPlayerHUD* APlayerCharacter::GetHUD()
{
	// Get the HUD widget.
	return m_pHUD;
}

FHitResult APlayerCharacter::GetHitResult()
{
	// Return the hit result attached to the line trace.
	return m_Hit;
}

FHitResult APlayerCharacter::GetWeaponHitResult()
{
	return m_WeaponHit;
}

bool APlayerCharacter::GetIsDashing()
{
	// Return the dashing state.
	return m_bIsDashing;
}

bool APlayerCharacter::GetLockedState()
{
	// Return the dashing state.
	return m_bIsMovementLocked;
}