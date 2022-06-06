// Fill out your copyright notice in the Description page of Project Settings.

#include "Item_ThrowableModule.h"
#include "Kismet/GameplayStatics.h"

AItem_ThrowableModule::AItem_ThrowableModule()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AItem_ThrowableModule::Attach(USceneComponent* AttachPosition)
{
	bHasTarget = false;

	// Play charged audio sound to indicate to player that the module has attached.
	UGameplayStatics::PlaySound2D(GetWorld(), AttachSFX, 1);

	Mesh->SetSimulatePhysics(false);

	// Reset collision profile to allow for linetrace detection.
	Mesh->SetCollisionProfileName("PhysicsActor");

	Mesh->AttachToComponent(AttachPosition, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AItem_ThrowableModule::Detach()
{
	Mesh->SetSimulatePhysics(true);

	// Play charged audio sound to indicate to player that the module is detached.
	UGameplayStatics::PlaySound2D(GetWorld(), AttachSFX, 1);

	// Reset the linear damping.
	Mesh->SetLinearDamping(0);

	Mesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
}


