// Fill out your copyright notice in the Description page of Project Settings.


#include "CorrupterFlyingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UCorrupterFlyingComponent::UCorrupterFlyingComponent ( )
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCorrupterFlyingComponent::BeginPlay ( )
{
    Super::BeginPlay ( );

    // Set Gravity to 0 to float the enemy
    AActor* const owner = GetOwner ( );
    m_pcNPC = Cast<AEnemyCorrupter> ( owner );
    //character->GetCharacterMovement ( )->GravityScale = 0;

    m_FlyingAudioComponent      = UGameplayStatics::SpawnSoundAtLocation ( GetWorld ( ) , m_FlyingSFX , GetOwner ( )->GetActorLocation ( ) , GetOwner ( )->GetActorRotation ( ) , 1.0F , 1.0F , 0.0F , m_FlyingAttenuation );
    m_AttackingAudioComponent   = UGameplayStatics::SpawnSoundAtLocation ( GetWorld ( ) , m_FlyingSFX , GetOwner ( )->GetActorLocation ( ) , GetOwner ( )->GetActorRotation ( ) , 1.0F , 1.0F , 0.0F );
    init = true;
}


// Called every frame
void UCorrupterFlyingComponent::TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
    Super::TickComponent ( DeltaTime , TickType , ThisTickFunction );

    if ( !init )
        return;

    // Based on states
    if ( m_pcNPC->eCurrentState == EEnemyCorrupterStates::Attacking )
    {
        m_FlyingAudioComponent->SetVolumeMultiplier ( 1 );
        m_AttackingAudioComponent->SetVolumeMultiplier ( 0 );
    }
    else
    {
        m_FlyingAudioComponent->SetVolumeMultiplier ( 1 );
        m_AttackingAudioComponent->SetVolumeMultiplier ( 0 );
    }
    
}

void UCorrupterFlyingComponent::DestroySound ( )
{
    if ( m_FlyingAudioComponent != nullptr && m_AttackingAudioComponent != nullptr)
    {
        m_FlyingAudioComponent->SetVolumeMultiplier ( 0 );
        m_AttackingAudioComponent->SetVolumeMultiplier ( 0 );
        m_FlyingAudioComponent->Stop ( );
        m_AttackingAudioComponent->Stop ( );
        m_FlyingAudioComponent->DestroyComponent ( );
        m_AttackingAudioComponent->DestroyComponent ( );
    }
}


