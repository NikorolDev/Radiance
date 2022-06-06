// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CorrupterProjectile.generated.h"

UCLASS()
class RADIANCE_API ACorrupterProjectile : public AActor
{
	GENERATED_BODY()

public:

    // Sets default values for this actor's properties
    ACorrupterProjectile ( );

    // Called every frame
    virtual void Tick ( float DeltaTime ) override;

    UPROPERTY ( VisibleDefaultsOnly )
        class USphereComponent* CollisionSphere;

    UPROPERTY ( VisibleDefaultsOnly , BlueprintReadOnly )
        class UProjectileMovementComponent* ProjectileMovement;

    UFUNCTION ( )
        void OnHit ( UPrimitiveComponent* HitComp , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& Hit );

    UPROPERTY ( EditAnywhere )
        float DamageValue = 20.0f;

    UPROPERTY ( EditAnywhere )
        bool IsHomingProjectile = true;

    float Distance;
    float MinDistance;
    FVector InitialLaunchVector;

protected:

    // Called when the game starts or when spawned
    virtual void BeginPlay ( ) override;

};
