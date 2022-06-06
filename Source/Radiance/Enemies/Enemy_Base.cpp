// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Base.h"
#include "Radiance/Enemies/Corrupter/CorrupterFlyingComponent.h"

// Sets default values
AEnemy_Base::AEnemy_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();	
}

// Enemy Die Sequence
void AEnemy_Base::Die ( bool IsReset )
{
	InvokeAttackOver ( true );

	// Destroy the Moving Sound
	UCorrupterFlyingComponent* component = FindComponentByClass<UCorrupterFlyingComponent> ( );
	if ( component != nullptr )
	{
		component->DestroySound ( );
	}

	// Broadcast EnemyDie
	EnemyDie.Broadcast ( this , IsReset );
	
	// Destory Instance
	Destroy ( );
}

// Called every frame
void AEnemy_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Attack Sequence is over
void AEnemy_Base::InvokeAttackOver ( bool state )
{
	IsAttackOver.Broadcast ( state );
}

