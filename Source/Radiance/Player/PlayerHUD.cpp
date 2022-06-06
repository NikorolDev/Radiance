// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Radiance/Inventory/InventoryManager.h"
#include "PlayerCharacter.h"
#include "Radiance/Tooltips/TooltipManager.h"
#include "Components/RichTextBlock.h"
#include "Components/ProgressBar.h"

UPlayerHUD::~UPlayerHUD()
{

}

void UPlayerHUD::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	m_fDeltaTime = DeltaTime;

	DashCooldown();
}

void UPlayerHUD::Initialise(APlayerCharacter* pPlayerCharacter)
{
	Battery->SetVisibility(ESlateVisibility::Visible);
	BatteryPercentage->SetVisibility(ESlateVisibility::Hidden);
	// Reference the player character.
	m_pPlayerCharacter = pPlayerCharacter;

	m_fCurrentDashCooldown = 0;

	// Hide the dash charge.
	DashCooldownBar->SetVisibility(ESlateVisibility::Visible);

	// Hide the no charge alert.
	ShowNoChargeAlert(ESlateVisibility::Hidden);
	ChargeCountBar->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerHUD::ChangeCrosshairColor(FColor fNewColor)
{
	// Change the color of the crosshair.
	Crosshair->SetColorAndOpacity(FLinearColor(fNewColor));
}

void UPlayerHUD::UpdateHealth(float fCurrentHealth)
{
	// Sets the size of the bar based on the players 
	HealthBar->SetPercent(fCurrentHealth);
}

void UPlayerHUD::UpdateCurrentCharge(float fCurrentCharge, float fMaxCharge)
{
	// Change the percent of the bar to show the players weapon charge.
	ChargeCountBar->SetPercent(fCurrentCharge / fMaxCharge);

	if (fCurrentCharge == fMaxCharge)
	{
		// Hide the visibility of the charge bar if the charge is at max.
		ChargeCountBar->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPlayerHUD::SetBarChargeVisibility(ESlateVisibility eVisibility)
{
	ChargeCountBar->SetVisibility(eVisibility);
}

void UPlayerHUD::ShowNoChargeAlert(ESlateVisibility eVisibility)
{
	// Show/hide the no charge alert based on the parameter.
	NoChargeAlert->SetVisibility(eVisibility);
}

void UPlayerHUD::SetInteractTextVisibility(ESlateVisibility eVisibility)
{
	InteractText->SetVisibility(eVisibility);
}

void UPlayerHUD::SetTooltipProperties( FString psTooltipText, UTexture2D* pcTooltipTexture )
{
	// Set the text of the tooltip.
	Tooltip->SetText( FText::FromString( psTooltipText ) );

	// Check if the tooltip texture 
	if( pcTooltipTexture != nullptr )
	{
		// Set the visibility of the tooltip image and then set the image.
		TooltipIcon->SetVisibility( ESlateVisibility::Visible );
		TooltipIcon->SetBrushFromTexture( pcTooltipTexture, true );
	}
	else
	{
		// Collapse the image so it is collapsed, which means only the text show up on the tooltip bar.
		TooltipIcon->SetVisibility( ESlateVisibility::Collapsed );
	}


	UE_LOG( LogTemp, Display, TEXT( "%s IS NOW PLAYING FORWARD" ), *MoveTooltip->GetName() );

	// Play the animation.
	m_bIsTooltipMovingIn = true;
	PlayAnimation( MoveTooltip );
}

void UPlayerHUD::HideTooltip()
{
	UE_LOG( LogTemp, Display, TEXT( "%s IS NOW PLAYING IN REVERSE" ), *MoveTooltip->GetName() );

	//Play the animation in reverse.
	m_bIsTooltipMovingIn = false;
	PlayAnimationReverse( MoveTooltip );
}

void UPlayerHUD::DashCooldown()
{
	if (m_bDashCooldown)
	{
		m_fCurrentDashCooldown += m_fDeltaTime;
		if (m_fCurrentDashCooldown <= m_pPlayerCharacter->fDashCooldown)
		{
			DashCooldownBar->SetPercent(m_fCurrentDashCooldown / m_pPlayerCharacter->fDashCooldown);
		}
		else
		{
			m_fCurrentDashCooldown = 0;
			//DashCooldownBar->SetVisibility(ESlateVisibility::Hidden);
			m_bDashCooldown = false;
			m_pPlayerCharacter->ResetDash();
		}
	}
}

void UPlayerHUD::TakeDamage()
{
	PlayAnimation(TakeDamageAnim);
}

void UPlayerHUD::OutOfTimerAlert()
{
	PlayAnimation(TimerAlert);
}

void UPlayerHUD::InflateCrosshair()
{
	PlayAnimation(CrosshairInflate);
}

void UPlayerHUD::SetDashCooldownVisibility(bool bIsDashCooldownVisible)
{
	//DashCooldownBar->SetVisibility(ESlateVisibility::Visible);
	m_bDashCooldown = bIsDashCooldownVisible;
}

UProgressBar* UPlayerHUD::GetChargeCountBar()
{
	return ChargeCountBar;
}

void UPlayerHUD::SetLoopTimeRemaining(float fRemainingTime, float fLoopMaxTime)
{
	FString sLoopTimer;

	Battery->SetPercent(FMath::Lerp(Battery->Percent, fRemainingTime / fLoopMaxTime, m_fDeltaTime * 30));

	float fCurrentCharge = (fRemainingTime / fLoopMaxTime) * 100;
	BatteryPercentage->SetText(FText::FromString(FString::FromInt(fRemainingTime)));

	if (fRemainingTime <= 11 && fRemainingTime > 0.2f)
	{
		BatteryPercentage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		BatteryPercentage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPlayerHUD::SetLoopCount(int32 iCurrentLoop)
{
	FString sLoopCount = FString::FromInt(iCurrentLoop);
	LoopCount->SetText(FText::FromString(sLoopCount));
}

void UPlayerHUD::RefreshDatabaseUpdatedAlert(FName Name, int32 Quantity)
{
	// When an item is added
	if (Quantity > 0)
	{
		// Set alert text and make it visible
		DatabaseUpdatedAlert->SetText(FText::FromString("Database updated:" + Name.ToString()));
		DatabaseUpdatedAlert->SetVisibility(ESlateVisibility::Visible);
	
		// Create a lambda function to bind to timer delegate
		FTimerDelegate TimerCallback;
		TimerCallback.BindLambda([&] { DatabaseUpdatedAlert->SetVisibility(ESlateVisibility::Hidden); });
		
		// Set timer to hide the database alert after X seconds
		GetWorld()->GetTimerManager().SetTimer(m_DatabaseUpdatedAlertHandle, TimerCallback, m_TimeToDisplayDatabaseAlert, false);
	}


}

void UPlayerHUD::AnimationFinished()
{
	// Check if the tooltip is moving in.
	if( m_bIsTooltipMovingIn )
	{
		// Display the tooltips. This will delay the display of the tooltips before moving back.
		UE_LOG( LogTemp, Display, TEXT( "DISPLAY TOOLTIP FOR DURATION SET" ) );
		m_pcTooltipManager->DisplayTooltip();
	}
	else
	{
		// Set the tooltips, which will either set the next tooltip or close the tooltips completely.
		m_pcTooltipManager->SetTooltip();
	}
}

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	// Retrieve inventory manager level instance
	m_InventoryManager = Cast<AInventoryManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AInventoryManager::StaticClass()));

	// Bind to the Inventory Changed delegate if the Inventory Manager is not null
	if (m_InventoryManager)
	{
		m_InventoryManager->InventoryChanged.AddDynamic(this, &UPlayerHUD::RefreshDatabaseUpdatedAlert);

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("No Inventory Manager class or blueprint in the level"));
	}

	// Hide the alert at start
	DatabaseUpdatedAlert->SetVisibility(ESlateVisibility::Hidden);

	// Get the tooltip manager from the level. (Nikodem Hamrol)
	m_pcTooltipManager = Cast<ATooltipManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ATooltipManager::StaticClass() ) );

	// Setup animation dynamic event, so that a function can be stored in this to be called when aniamtion is finished. (Nikodem Hamrol)
	FWidgetAnimationDynamicEvent fsTooltipWidgetAnimation;

	// Using the dynamic event, store the function as delegate which will be called. (Nikodem Hamrol).
	fsTooltipWidgetAnimation.BindDynamic( this, &UPlayerHUD::AnimationFinished );

	// Then bind the it to the animation so the callback will be called when the animation is finished. (Nikodem Hamrol)
	BindToAnimationFinished( MoveTooltip, fsTooltipWidgetAnimation );

}
