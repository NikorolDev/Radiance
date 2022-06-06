// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Base.h"
#include "Kismet/GameplayStatics.h"
#include "Radiance/Player/PlayerCharacter.h"
#include "Radiance/Player/PlayerHUD.h"
#include "Components/PointLightComponent.h"
#include "Radiance/Player/Projectile.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ProgressBar.h"
#include "Curves/CurveLinearColor.h"

// Sets default values
AWeapon_Base::AWeapon_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Orb = CreateDefaultSubobject<UStaticMeshComponent>("Orb");

	// Create the mesh and disable collision.
	Light = CreateDefaultSubobject<UPointLightComponent>("Light Orb");
	Light->SetupAttachment(Orb);
}

void AWeapon_Base::Initialise(APlayerCharacter* pPlayerCharacter)
{
	// Reference the player character.
	m_pPlayer = pPlayerCharacter;

	// Update the weapon charge on the HUD.
	m_pPlayer->GetHUD()->UpdateCurrentCharge(fCurrentCharge, fMaxCharge);

	// Attach the weapon to a specified socket on the mesh.
	AttachToComponent(m_pPlayer->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("WeaponPos"));

	for (int i = 0; i < fMaxCharge; i++)
	{
		Projectiles.Add(GetWorld()->SpawnActor<AProjectile>(Projectile));
	}

	ShotFlash = UGameplayStatics::SpawnEmitterAttached(ShotFlashTemplate, Orb, FName(), Orb->GetComponentLocation(), Orb->GetComponentRotation(), EAttachLocation::SnapToTarget, false, EPSCPoolMethod::None, false);
}

// Called when the game starts or when spawned
void AWeapon_Base::BeginPlay()
{
	Super::BeginPlay();

	Light->SetVisibility(false);

}

// Called every frame
void AWeapon_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fDeltaTime = DeltaTime;

	// Called every frame to charge the weapon if required.
	Recharge();

	CooldownHandler();
}

bool AWeapon_Base::CheckActiveState()
{
	for (AProjectile* i : Projectiles)
	{
		if (!i->GetActiveState() && i->GetCanBeFired())
		{
			m_pcActiveProjectile = i;
			return true;
		}
	}
	return false;
}

void AWeapon_Base::CooldownHandler()
{
	FLinearColor A = m_pPlayer->GetHUD()->GetChargeCountBar()->FillColorAndOpacity;
	FLinearColor B = CooldownCurve->GetLinearColorValue(fCurrentCharge / fMaxCharge);
	FLinearColor NewColor = UKismetMathLibrary::LinearColorLerp(A, B, (fCurrentCharge / fMaxCharge));
	m_pPlayer->GetHUD()->GetChargeCountBar()->SetFillColorAndOpacity(NewColor);
}

void AWeapon_Base::BeginShoot()
{
	// Checks to see if there is a blocking hit.
	if (m_pPlayer->GetHitResult().bBlockingHit)
	{
		if (CheckActiveState())
		{
			Shoot();
		}
		else
		{
			BeginCharge();
		}
	}
}

void AWeapon_Base::Shoot()
{
	if (fCurrentCharge > 0 && CheckActiveState())
	{
		if (ShotFlash->IsActive())
		{
			ShotFlash->Deactivate();
		}


		// Fire a projectile.
		ShotFlash->Activate();

		m_pcActiveProjectile->ProjectileShot(m_pPlayer->GetMesh()->GetSocketLocation(FName("Gauntlet")), m_pPlayer->GetWeaponHitResult().ImpactPoint, m_pPlayer->GetCameraComponent()->GetComponentRotation());
		m_pcActiveProjectile = nullptr;

		m_pPlayer->Shoot();

		// Show the gauntlet charge.
		m_pPlayer->GetHUD()->SetBarChargeVisibility(ESlateVisibility::Visible);
			
		Light->SetVisibility(true);

		// Clear the timers that begin the recharge of the weapon as it is in use.
		GetWorldTimerManager().ClearTimer(m_ChargeTimer);
		GetWorldTimerManager().ClearTimer(m_BeginChargeTimer);

		// Lower the current charge value as a bullet was shot.
		fCurrentCharge -= 1;


		m_pPlayer->GetHUD()->UpdateCurrentCharge(fCurrentCharge, fMaxCharge);

		// Play the bullet audio and spawn emitter at location of fire.
		UGameplayStatics::PlaySound2D(GetWorld(), WeaponShoot, 1);

		// Call a function every 'x' seconds.
		GetWorldTimerManager().SetTimer(m_ShootTimer, this, &AWeapon_Base::Shoot, fTimeBetweenShots, true);
	}
	else
	{
		m_pPlayer->GetHUD()->ShowNoChargeAlert(ESlateVisibility::Visible);
		EndShoot();
	}
}

void AWeapon_Base::EndShoot()
{
	GetWorldTimerManager().ClearTimer(m_BeginShootTimer);

	Light->SetVisibility(false);

	// Clear and set the correct timers as player has stopped shooting.
	GetWorldTimerManager().ClearTimer(m_ShootTimer);
	GetWorldTimerManager().SetTimer(m_BeginChargeTimer, this, &AWeapon_Base::BeginCharge, fTimeBeforeRecharge, false);
}

void AWeapon_Base::AddCharge()
{
	// Increase charge value.
	fCurrentCharge++;

	// Allow for another charge to be added.
	m_bAddCharge = false;

	// Update charge.
	m_pPlayer->GetHUD()->UpdateCurrentCharge(fCurrentCharge, fMaxCharge);
}

void AWeapon_Base::BeginCharge()
{
	// If the charge is not already max then allow for the recharge to begin.
	if (fCurrentCharge < fMaxCharge)
	{
		// Start recharge.
		m_bRecharge = true;
		m_bAddCharge = false;
		m_bChargeStarted = false;

		// Hide the alert saying 'no charge'.
		m_pPlayer->GetHUD()->ShowNoChargeAlert(ESlateVisibility::Hidden);
	}
}

void AWeapon_Base::Recharge()
{
	// Recharge sequence.
	if (m_bRecharge && !m_bAddCharge)
	{
		// Max sure current charge is not max.
		if (fCurrentCharge < fMaxCharge)
		{
			m_bAddCharge = true;
			GetWorldTimerManager().SetTimer(m_ChargeTimer, this, &AWeapon_Base::AddCharge, fChargeDuration / fMaxCharge, true);
		}
		else
		{
			// Stop recharge if max.
			m_bRecharge = false;

			// Reset timers.
			GetWorldTimerManager().ClearTimer(m_ChargeTimer);
			GetWorldTimerManager().ClearTimer(m_BeginChargeTimer);
		}
	}
}
