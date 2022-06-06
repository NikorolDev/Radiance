// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_Base.generated.h"

// Class references.
class APlayerCharacter;
class APlayerHUD;
class UPointLightComponent;
class AProjectile;
class UParticleSystem;
class UCurveLinearColor;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			:	AWeapon_Base
// Author				:	Kurtis Watson
// Inherits				:	AActor - Inherited so it is able to be placed in the world.
// Purpose				:	Class that stores all default properties of a weapon, allowing for several variations of a weapon.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API AWeapon_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		:	AWeapon_Base
	// Author				:	Kurtis Watson
	//-----------------------------------------------------------------------------------------------------------------------------
	AWeapon_Base();

	// The mesh of the weapon.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (DisplayName = "Orb"))
		UStaticMeshComponent* Orb;

	// The mesh of the weapon.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (DisplayName = "Light"))
	UPointLightComponent* Light;

	// Used to spawn a weapon in game.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectile> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (DisplayName = "Light"))
	TArray<AProjectile*> Projectiles;

	// Determines if the player is in the gravity state.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic")
		UCurveLinearColor* CooldownCurve;

	UParticleSystemComponent* ShotFlash;

	// The time between shots.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (DisplayName = "Time Before Recharge"))
		float fTimeBeforeRecharge;

	// The time between shots.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (DisplayName = "Time Between Shots"))
	float fTimeBetweenShots;

	// Max charge of the weapon.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (DisplayName = "Max Charge"))
	float fMaxCharge;

	// Current charge of the weapon.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (DisplayName = "Current Charge"))
	float fCurrentCharge;

	// How long it takes to fully charge the weapon.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (DisplayName = "Charge Duration"))
	float fChargeDuration;

	// Sound to play when the weapon is fired.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
	USoundWave* WeaponShoot;

	// Determines if player is shooting or not.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (DisplayName = "Shot Flash"))
		UParticleSystem* ShotFlashTemplate;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Initialise
	// Author				:	Kurtis Watson
	// Purpose				:	Called at game begin.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Initialise(APlayerCharacter* pPlayerCharacter);

protected:
	// Reference the player.
	APlayerCharacter* m_pPlayer;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	BeginPlay
	// Author				:	UE4
	// Purpose				:	Called at game begin.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	AddCharge
	// Author				:	Kurtis Watson
	// Purpose				:	Adds charge to the weapon.
	//-----------------------------------------------------------------------------------------------------------------------------
	void AddCharge();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	BeginCharge
	// Author				:	Kurtis Watson
	// Purpose				:	Begins the charging of the weapon.
	//-----------------------------------------------------------------------------------------------------------------------------
	void BeginCharge();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Recharge
	// Author				:	Kurtis Watson
	// Purpose				:	Recharges the weapon over a set duration.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Recharge();

public:	

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Shoot
	// Author				:	Kurtis Watson
	// Purpose				:	Shoots the weapon, plays audio and emitts particles.
	//-----------------------------------------------------------------------------------------------------------------------------
	void Shoot();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	EndShoot
	// Author				:	Kurtis Watson
	// Purpose				:	Called to recognise when the player is not longer shooting.
	//-----------------------------------------------------------------------------------------------------------------------------
	void EndShoot();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	BeginShoot
	// Author				:	Kurtis Watson
	// Purpose				:	Called to recognise when the player has began to shoot.
	//-----------------------------------------------------------------------------------------------------------------------------
	void BeginShoot();

private:
	// Timers.
	FTimerHandle	m_ShootTimer;
	FTimerHandle	m_ChargeTimer;
	FTimerHandle	m_BeginChargeTimer;
	FTimerHandle	m_BeginShootTimer;

	AProjectile*	m_pcActiveProjectile;

	// Used to recognise whether or not to charge the weapon.
	bool			m_bRecharge;
	bool			m_bAddCharge;
	bool			m_bChargeStarted;

	// Holds the deltatime so it can be accessed anywhere within the class.
	float			m_fDeltaTime;

	// Holds the current crosshair color.
	FLinearColor	m_CurrentCrosshairColor;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Tick
	// Author				:	UE4
	// Purpose				:	Called each frame (update).
	// Parameters			:	DeltaTime - Calculates the time different between previous and current frame.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void Tick(float DeltaTime) override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	CheckActiveState
	// Author				:	Kurtis Watson
	// Purpose				:	Checks the active state of the projectiles.
	//-----------------------------------------------------------------------------------------------------------------------------
	bool CheckActiveState();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	CooldownHandler
	// Author				:	Kurtis Watson
	// Purpose				:	Handles the colour of the cooldown bar when firing.
	//-----------------------------------------------------------------------------------------------------------------------------
	void CooldownHandler();
};
