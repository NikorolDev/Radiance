// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_ThrowableBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Sound/SoundBase.h"

AItem_ThrowableBarrel::AItem_ThrowableBarrel ( )
{
	PrimaryActorTick.bCanEverTick = true;

	// Creating the Radial Force Component
	Force = CreateDefaultSubobject<URadialForceComponent> ( TEXT ( "Force" ) );

	Mesh->SetCollisionEnabled ( ECollisionEnabled::QueryAndPhysics );
}

void AItem_ThrowableBarrel::BeginPlay ( )
{
	Super::BeginPlay ( );

	// Setup an OnComponentBeginOverlap callback function to be called when an overlap is triggered.
	Mesh->OnComponentHit.AddDynamic(this, &AItem_ThrowableBarrel::OnComponentHit);

	// Set stimulate physics to true 
	Mesh->SetSimulatePhysics ( true );

	auto Object=FindComponentByClass<UStaticMeshComponent> ( );
	auto Material = Object->GetMaterial ( 0 );

	DynamicMaterial = UMaterialInstanceDynamic::Create ( Material, NULL );

	Mesh->SetMaterial ( 0, DynamicMaterial );

}
void AItem_ThrowableBarrel::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnComponentHit (HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	// Calling the Explode() function
	Explode ( );   
}

void AItem_ThrowableBarrel::Explode ( )
{
	if ( bThrown )
	{
		GEngine->AddOnScreenDebugMessage ( -1, 5.f, FColor::Green, TEXT ( "BARREL EXPLOSION" ) );

		Mesh->SetCollisionEnabled ( ECollisionEnabled::NoCollision );

		// Spawning the SFX and VFX 
		UGameplayStatics::SpawnSoundAtLocation ( this, ExplosionSound, GetActorLocation ( ) );
		UGameplayStatics::SpawnEmitterAtLocation ( this, ExplosionVFX, GetActorLocation ( ) );

		// Adding Force to the actor
		Force->FireImpulse ( );
		Mesh->AddImpulse ( FVector ( 0, 0, 61000 ), NAME_None, true );

		//DynamicMaterial->SetVectorParameterValue ( "lambert1", FLinearColor::Black );
	}

	}
	// Changing the material's colour to black
	


