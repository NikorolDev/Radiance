// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"
//#include "Blueprint/UserWidget.h"
#include "Radiance/Enemies/Corrupter/EnemyCorrupter.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::NativeConstruct ( )
{
    Super::NativeConstruct ( );

    //m_HealthBar->SetPercent ( m_EnemyOwner->GetHealthBarPercentage() );
}
//
void UHealthBarWidget::NativeTick ( const FGeometry& MyGeometry , float InDeltaTime )
{
	Super::NativeTick ( MyGeometry , InDeltaTime );

	if ( m_EnemyOwner == nullptr )
		return;

	m_HealthBar->SetPercent ( m_EnemyOwner->GetHealthBarPercentage ( ) );
}

// Set owner of this Widget
void UHealthBarWidget::SetOwner ( AEnemyCorrupter* value )
{
    m_EnemyOwner = value;
    m_EnemyOwner->TakeHitDamage.AddDynamic ( this, &UHealthBarWidget::UpdateHealthBar );
    UpdateHealthBar ( 0 );
}

// Set the Health bar percentage
float UHealthBarWidget::GetHealthbarPercentage ( ) const
{
    float percentage = m_EnemyOwner->GetHealthBarPercentage ( );
    m_HealthBar->SetPercent ( 1.0F );
    return 0.0F;
}

// Update the Health bar percentage
void UHealthBarWidget::UpdateHealthBar ( float DamageAmount )
{
    float percentage = m_EnemyOwner->GetHealthBarPercentage ( );
    m_HealthBar->SetPercent ( percentage );
}
