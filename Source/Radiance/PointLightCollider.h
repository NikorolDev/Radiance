// Fill out your copyright notice in the Description page of Project Settings.
//-----------------------------------------------------------------------------------------------------------------------------
// Class Name		    : PointLightCollider 
// Author				: Michalis Stratis
// Editors				: Michalis Stratis
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointLightCollider.generated.h"

class USphereComponent;

UCLASS()
class RADIANCE_API APointLightCollider : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APointLightCollider();

	// Prints On Screen wether player is in the light or not
	void PrintOnScreen ( bool bInLight );

	// Disables Colliders
	void DisableColliders ( );

	//Enables Colliders
	void EnableColliders ( );

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Setting a sphere collider component as a UProperty
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "POINT LIGHT")
		class USphereComponent* SphereCollider;

	// Setting a point light component as a UProperty
	UPROPERTY(VisibleAnywhere, Category = "POINT LIGHT")
		class UPointLightComponent* PointLight;

	// Setting light intensity float as a UProperty
	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
		float m_fLightIntensity;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool m_bInLight=true;									// Boolean, true if player is in light flase if in dark
	FTimerHandle m_TimerHandle;								// FTimerHandle, for timer in insannity meter
	FString m_cPercentageString;							// FString, for converting a float to string
	float m_fCallTracker=2;									// Float, for the countdown of the timer
	float m_fPercent;										// Float, for the insanity percentage presented on screen

	// Deducts time for player insanity meter
	void DeductTime ( );

	// Adds time for player insanity meter
	void AddTimeFunction ( );

	// Overlap Events
	UFUNCTION ( )
		void OnOverlapBegin ( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION ( )
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};

