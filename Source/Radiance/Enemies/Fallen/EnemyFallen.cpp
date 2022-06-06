// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFallen.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "CollisionShape.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AEnemyFallen::AEnemyFallen()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyFallen::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyFallen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyFallen::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Blast itself and cause surrounding damage
void AEnemyFallen::Attack ( )
{
	// Get mesh component and World
	USkeletalMeshComponent* const mesh = GetMesh ( );
	UWorld* world = GetWorld ( );
		
	// Spaw particle effect on blast
	UGameplayStatics::SpawnEmitterAtLocation ( world, m_BlastVFX, mesh->GetComponentLocation(), FRotator::ZeroRotator, FVector::OneVector, true,EPSCPoolMethod::AutoRelease, true );

	// Add impulse to the surrounding objects
	m_RadialForceComponent->FireImpulse ( );
	
	// Play SFX
	UGameplayStatics::PlaySoundAtLocation ( world, m_BlastSFX, mesh->GetComponentLocation ( ) , 1.0f, 1.0f, 0.0f);

	// Get allow collidable objects in the collision sphere radius
	TArray< struct FHitResult > outHits = TArray< struct FHitResult > ( );
	FCollisionShape collisionSphere = FCollisionShape::MakeSphere ( 400.0f );
	world->SweepMultiByChannel ( OUT outHits , GetActorLocation ( ) , GetActorLocation ( ) + FVector::UpVector * collisionSphere.GetSphereRadius ( ) , FQuat ( ) , ECollisionChannel::ECC_WorldDynamic , collisionSphere );

	// loop through all collidable objects and add damage
	for ( FHitResult&hit : outHits )
	{
		FHitResult outLine = FHitResult ( );
		world->LineTraceSingleByChannel ( OUT outLine , GetActorLocation ( ) , hit.ImpactPoint , ECollisionChannel::ECC_Visibility , FCollisionQueryParams::DefaultQueryParam , FCollisionResponseParams::DefaultResponseParam );

		APlayerController* const playerController = Cast<APlayerController> ( UGameplayStatics::GetPlayerController ( GetWorld ( ) , 0 ) );
		ACharacter* const playerCharacter = Cast<ACharacter> ( playerController->GetCharacter ( ) );
		
		// Damage player, can be done using distance and impact to get a variable amount
		if ( outLine.GetActor() == playerCharacter )
		{
			UGameplayStatics::ApplyDamage ( outLine.GetActor(), 20, playerController , this , UDamageType::StaticClass ( ) );
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("DAMAGED: %s"), outLine.GetActor()));
		}
	}

	// Kill the Enemy
	Destroy ( );
}
