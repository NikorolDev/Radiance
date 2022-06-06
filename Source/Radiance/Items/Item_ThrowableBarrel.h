// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Throwable.h"
#include "Item_ThrowableBarrel.generated.h"

class URadialForceComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;

UCLASS()
class RADIANCE_API AItem_ThrowableBarrel : public AItem_Throwable
{
	GENERATED_BODY()

public:
	AItem_ThrowableBarrel ( );

	virtual void BeginPlay ( ) override;
protected:

	// Radia force Component
	UPROPERTY ( EditAnywhere, Category = "Components" )
		URadialForceComponent* Force;

	// VFX for explosion
	UPROPERTY ( EditDefaultsOnly, Category = "Effects" )
		UParticleSystem* ExplosionVFX;

	// Setting the dynamic material
	UPROPERTY ( EditDefaultsOnly, Category = "Effects" )
		UMaterialInstanceDynamic* DynamicMaterial;

	// SFX For explosion
	UPROPERTY ( EditAnywhere, Category = "Effects" )
		bool bUse;

	// SFX For explosion
	UPROPERTY ( EditAnywhere, Category = "Player" )
		class USoundBase* ExplosionSound;

public: 
	//virtual void Tick ( float DeltaTime ) override;
	void Explode ( );

	// Called when this object hits another.
	virtual void OnComponentHit (UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit ) override;
};
