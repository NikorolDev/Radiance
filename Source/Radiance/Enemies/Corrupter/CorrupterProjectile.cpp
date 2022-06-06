// Fill out your copyright notice in the Description page of Project Settings.


#include "CorrupterProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACorrupterProjectile::ACorrupterProjectile ( )
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent> ( TEXT ( "Sphere Collision" ) );
	CollisionSphere->InitSphereRadius ( 20.0f );

	RootComponent = CollisionSphere;

	//ProjectileMovement->SetVelocityInLocalSpace(suggestProjectile);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent> ( TEXT ( "Projectile Movement" ) );
	ProjectileMovement->UpdatedComponent = CollisionSphere;
	ProjectileMovement->InitialSpeed = 100.0f;
	ProjectileMovement->MaxSpeed = 200.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->Velocity = FVector ( 0 , 0 , 0 );

	IsHomingProjectile = false;
	InitialLifeSpan = 13.0f;

	Distance = 0.0f;
	MinDistance = 0.0f;
	InitialLaunchVector = GetActorForwardVector ( );

}

// Called when the game starts or when spawned
void ACorrupterProjectile::BeginPlay ( )
{
	Super::BeginPlay ( );

	float projectileSpeed = 50;

	ACharacter* const player = UGameplayStatics::GetPlayerCharacter ( GetWorld ( ) , 0 );


	float div = GetDistanceTo ( player ) / projectileSpeed;
	FVector mult = player->GetVelocity ( ) * div;
	FVector add = player->GetActorLocation ( ) + mult;

	const FCollisionResponseParams responseParams;
	FVector TossVelocity = FVector ( 0 , 0 , 0 );
	const TArray<AActor*>& ActorToIgnore = TArray<AActor*> ( { this } );
	bool suggestProjectile = UGameplayStatics::SuggestProjectileVelocity ( GetWorld ( ) , OUT TossVelocity , GetActorLocation ( ) , add , projectileSpeed , false , 20.0f , 0.0F , ESuggestProjVelocityTraceOption::DoNotTrace , responseParams , ActorToIgnore , true );

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Proj: %d"), suggestProjectile));
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Toss: %s"), *(TossVelocity.ToString())));

	if ( player != nullptr )
	{
		const FVector ShootDirection = player->GetActorLocation ( ) - GetActorLocation ( );
		//ProjectileMovement->Velocity = ProjectileMovement->InitialSpeed * add;
		//ProjectileMovement->Velocity = TossVelocity;
		//DrawDebugLine(GetWorld(), add, this->GetTargetLocation(), FColor::Red, false, 10.0f, 5, 5);
	}
	IsHomingProjectile = true;
	Distance = GetDistanceTo ( player );
	MinDistance = Distance;


	CollisionSphere->OnComponentBeginOverlap.AddDynamic ( this , &ACorrupterProjectile::OnHit );
}

// Called every frame
void ACorrupterProjectile::Tick ( float DeltaTime )
{
	Super::Tick ( DeltaTime );

	float HomingStrength = 2000.0f;
	if ( IsHomingProjectile )
	{
		/*
		{

		ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

		float HomingStrength = 1.0f;

		FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), player->GetActorLocation());
		FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), LookAt, DeltaTime, HomingStrength);
		SetActorRotation(NewRotation);

		FVector mul = GetActorForwardVector() * ProjectileMovement->Velocity;
		FVector NewRelativeLocation = mul + GetActorLocation();

		SetActorRelativeLocation(NewRelativeLocation);
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("Relative L: %s"), *(NewRelativeLocation.ToString())));

		//DrawDebugLine(GetWorld(), GetTargetLocation(), player->GetTargetLocation(), FColor::Red, false, 10.0f, 5, 5);
		}
		*/
		ACharacter* const player = UGameplayStatics::GetPlayerCharacter ( GetWorld ( ) , 0 );

		FRotator LookAt = UKismetMathLibrary::FindLookAtRotation ( InitialLaunchVector , GetActorLocation ( ) );

		FVector WantedDir = FVector ( 0 , 0 , 0 );
		float distance = GetDistanceTo ( player );
		//float minDistance = Distance;

		//if (abs(LookAt.Yaw) < 150)
		if ( distance > 150.0f )
		{
			WantedDir += player->GetVelocity ( ) * WantedDir.Size ( ) / HomingStrength;
			WantedDir = ( player->GetActorLocation ( ) - GetActorLocation ( ) ).GetSafeNormal ( );

			ProjectileMovement->Velocity += WantedDir * HomingStrength * DeltaTime;

			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("LookAt: %s"), *(LookAt.ToString())));
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("distance: %f"), Distance));
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("HomingL: %s"), *(ProjectileMovement->Velocity.ToString())));

			MinDistance = GetDistanceTo ( player );
		}
		else
		{
			ProjectileMovement->Velocity += WantedDir * HomingStrength * DeltaTime;
			IsHomingProjectile = false;
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, FString::Printf(TEXT("HomingL: Straight")));

		}
		ProjectileMovement->Velocity += ProjectileMovement->Velocity.GetSafeNormal ( ) * HomingStrength;
	}
	ProjectileMovement->Velocity += ProjectileMovement->Velocity.GetSafeNormal ( ) * HomingStrength;
}

void ACorrupterProjectile::OnHit ( UPrimitiveComponent* HitComp , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& Hit )
{
	if ( ( OtherActor != NULL ) && ( OtherActor != this ) && ( OtherComp != NULL ) )
	{
		GEngine->AddOnScreenDebugMessage ( -1 , 3.0f , FColor::Green , FString::Printf ( TEXT ( "HITTING: %s" ) , *OtherActor->GetName ( ) ) );
		if ( *OtherActor->GetName ( ) == UGameplayStatics::GetPlayerCharacter ( GetWorld ( ) , 0 )->GetName ( ) )
		{
			GEngine->AddOnScreenDebugMessage ( -1 , 3.0f , FColor::Red , FString::Printf ( TEXT ( "BLAST!" ) ) );
			Destroy ( );
		}
	}

}