// Fill out your copyright notice in the Description page of Project Settings.
//-----------------------------------------------------------------------------------------------------------------------------
// Class Name		    : LightSwitch
// Author				: Michalis Stratis
// Editors				: Michalis Stratis
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightSwitch.generated.h"


class USphereComponent;

UCLASS()
class RADIANCE_API ALightSwitch : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ALightSwitch();

	// Setting a sphere collider component as a UProperty
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "STATIC MESH COMPONENT")
		class UStaticMeshComponent* LightSwitchCollider;

	// Setting a point light component as a UProperty
	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
		class UPointLightComponent* PointLight;

	// Setting light intensity float as a UProperty
	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
		float m_fLightIntensity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Point Collider class 
	class APointLightCollider* PointLightCollider;

	// Changes visibillity of light ( On/Off )
	void ToggleLight ( );

	// Overlap Events
	UFUNCTION ( )
		void OnOverlapBegin ( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION ( )
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
