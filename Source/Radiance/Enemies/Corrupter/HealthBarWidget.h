// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

class UProgressBar;
class AEnemyCorrupter;
class AEnemy_Base;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ACombatManager
// Author				: Saurya Saurav
// Editors				: 
// Classes Inherited	: AActor , IInfluentiableThroughCycles
// Purpose				: This class is used to handle the combat with the enemies
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetOwner
	// Author			: Saurya Saurav
	// Parameters		: AEnemyCorrupter*
	// Purpose			: Set owner of this Widget
	//----------------------------------------------------------------------------------------------------------------------------
	void SetOwner ( AEnemyCorrupter* value ); 

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetHealthBar
	// Author			: Saurya Saurav
	// Return			: UProgressBar*
	// Purpose			: Getter for Progress Bar
	//----------------------------------------------------------------------------------------------------------------------------
	FORCEINLINE class UProgressBar* GetHealthBar ( ) { return m_HealthBar; }

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetHealthbarPercentage
	// Author			: Saurya Saurav
	// Purpose			: Set the Health bar percentage
	// NOTE				: Binded with progress in the editor
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION ( BlueprintCallable )
		float GetHealthbarPercentage ( ) const;
	
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: UpdateHealthBar
	// Author			: Saurya Saurav
	// Parameters		: float
	// Purpose			: Update the Health bar percentage
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION ( BlueprintCallable )
		void UpdateHealthBar ( float DamageAmount );

	// Progress Bar, bind with widget in the editor
	UPROPERTY ( meta = ( BindWidget ) )
		UProgressBar* m_HealthBar;

protected:

	virtual void NativeConstruct ( ) override;

	virtual void NativeTick ( const FGeometry& MyGeometry , float InDeltaTime ) override;

private:

	// Owner of the Widget
	AEnemyCorrupter* m_EnemyOwner;

};
