// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCorrupter.h"
#include "CorrupterAIController.h"
#include "Radiance/Enemies/BlackboardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Radiance/Player/PlayerCharacter.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include <Radiance/Player/Projectile.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <Runtime/Engine/Public/DrawDebugHelpers.h>
#include <Radiance/Enemies/Corrupter/CorrupterAnimInstance.h>

// Sets default values
AEnemyCorrupter::AEnemyCorrupter ( const FObjectInitializer& ObjectInitializer )
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create Health Widget
    //m_HealthWidgetComp = ObjectInitializer.CreateDefaultSubobject<UWidgetComponent> ( this , TEXT ( "HealthBar" ) );
    //m_HealthWidgetComp->AttachToComponent ( RootComponent , FAttachmentTransformRules::KeepRelativeTransform );
}

// Called when the game starts or when spawned
void AEnemyCorrupter::BeginPlay ( )
{
    Super::BeginPlay ( );

    // Get World
    m_World = GetWorld ( );

    // Set Current health as Initial health
    m_fCurrentHealth = m_fInitialHealth;

    // Enemy is in ideal state
    eCurrentState = EEnemyCorrupterStates::Idle;

    // Cast widget to health bar and set it's owner as this
    //UHealthBarWidget* HealthBar = Cast<UHealthBarWidget> ( m_HealthWidgetComp->GetUserWidgetObject ( ) );
    //HealthBar->SetOwner ( this );
    //TakeHitDamage.Broadcast ( 0 );
}

//To Initlize this instance of enemy
void AEnemyCorrupter::Init ( )
{
    // Adding callback on collision
    m_CapsuleComponent->OnComponentHit.AddDynamic ( this , &AEnemyCorrupter::OnHit );
}

// Called every frame
void AEnemyCorrupter::Tick ( float DeltaTime )
{
    Super::Tick ( DeltaTime );

    m_fDeltaTime = DeltaTime;
    ACorrupterAIController* const controller = Cast<ACorrupterAIController> ( GetController ( ) );
    APlayerController* const playerController = Cast<APlayerController> ( UGameplayStatics::GetPlayerController ( GetWorld ( ) , 0 ) );
    //UCorrupterAnimInstance* const anim = Cast<UCorrupterAnimInstance> ( GetMesh ( )->GetAnimInstance ( ) );

    //ACharacter* const playerCharacter = Cast<ACharacter> ( playerController->GetCharacter ( ) );

    if ( controller != nullptr )
    {
        // Move Enemy to location based on its movement state and blackboard key  
        if ( eCurrentState == EEnemyCorrupterStates::Attacking )
        {
            //anim->Attack = true;

            SetActorRelativeLocation ( MoveTowardsLocation ( GetActorLocation ( ) , controller->GetBlackboard ( )->GetValueAsVector ( BlackboardKeys::chTargetAttackLocation ) , m_fAttackMovementSpeed ) );
            //AddForceToMove ( GetActorLocation ( ) , controller->GetBlackboard ( )->GetValueAsVector ( BlackboardKeys::chTargetAttackLocation ) , m_fMovementSpeed + 200 );

        }
        else
        {
            //anim->Attack = false;

            //FVector Dimensions = FVector ( 300 , 0 , 0 );
            //FVector AxisVector = FVector ( 1 , 0 , 0 );
            //float Multiplier = 50.f;

            //FVector NewLocation = FVector ( 0 , 0 , 800 );


            //if ( AngleAxis >= 360.0f )
            //{
            //    AngleAxis = 0;
            //}


            ////FVector myCharacter = GetActorLocation ( );

            //FVector RotateValue = Dimensions.RotateAngleAxis ( AngleAxis , AxisVector );

            ////GEngine->AddOnScreenDebugMessage ( -1 , 5.f , FColor::Red , FString::Printf ( TEXT ( "RotateValue: %s" ) , *RotateValue.ToString ( ) ) );
            ////GEngine->AddOnScreenDebugMessage ( -1 , 5.f , FColor::Green , FString::Printf ( TEXT ( "AngleAxis: %f" ) , AngleAxis ) );

            //NewLocation.X += RotateValue.X;
            //NewLocation.Y += RotateValue.Y;
            //NewLocation.Z += RotateValue.Z;

            ////SetActorLocation ( NewLocation , false , 0 , ETeleportType::None );
            //SetActorRotation ( RotateValue.ToOrientationQuat ( ) , ETeleportType::None );

            AngleAxis += 5;
            //FVector Euler ( 0.f , AngleAxis , -90.0f );
            //FQuat QuatRotation;
            //QuatRotation.MakeFromEuler ( Euler );
            //SetActorRotation ( QuatRotation );
            //FRotator QuatRotation ;
            //QuatRotation.Euler().Y += 10;
            //SetActorRotation ( QuatRotation.Euler(Euler) );

            FRotator MyRot;
            MyRot.Roll = AngleAxis;
            MyRot.Pitch = GetActorRotation().Pitch;
            MyRot.Yaw = GetActorRotation ( ).Yaw;

            SetActorRotation(MyRot);
            //SetActorRelativeRotation ( MyRot );

            FVector TargetPos = controller->GetBlackboard ( )->GetValueAsVector ( BlackboardKeys::chTargetLocation ) - GetActorLocation ( );
            float Distance = TargetPos.Size ( );
            float actualMovementSpeed = 0;
            if ( Distance < 800 )
            {
                m_fAcceleration -= 5;
                //accelration = 500 * m_fDeltaTime;
                m_fAcceleration = FMath::Clamp ( m_fAcceleration , 0.0f , 400.0f );
                actualMovementSpeed = m_fMovementSpeed + m_fAcceleration;
                SetActorRelativeLocation ( MoveTowardsLocation ( GetActorLocation ( ) , controller->GetBlackboard ( )->GetValueAsVector ( BlackboardKeys::chTargetLocation ) , actualMovementSpeed ) );
                //GEngine->AddOnScreenDebugMessage ( -1 , 3.0f , FColor::Red , FString::Printf ( TEXT ( "Decrease Speed: %f" ) , actualMovementSpeed ) );
            }
            else if ( Distance < 1200 )
            {
                actualMovementSpeed = m_fMovementSpeed + m_fAcceleration;
                //actualMovementSpeed = FMath::Clamp ( m_fMovementSpeed + m_fAcceleration , 500.0f , 900.0f );
                SetActorRelativeLocation ( MoveTowardsLocation ( GetActorLocation ( ) , controller->GetBlackboard ( )->GetValueAsVector ( BlackboardKeys::chTargetLocation ) , actualMovementSpeed ) );
                //GEngine->AddOnScreenDebugMessage ( -1 , 3.0f , FColor::Red , FString::Printf ( TEXT ( "Constant Speed: %f" ) , actualMovementSpeed ) );
            }
            else
            {
                //accelration = 900 * m_fDeltaTime;
                m_fAcceleration += 1;
                m_fAcceleration = FMath::Clamp ( m_fAcceleration , 0.0f , 400.0f );
                actualMovementSpeed = m_fMovementSpeed + m_fAcceleration;
                //actualMovementSpeed = FMath::Clamp ( actualMovementSpeed , 500.0f , 1200.0f );
                SetActorRelativeLocation ( MoveTowardsLocation ( GetActorLocation ( ) , controller->GetBlackboard ( )->GetValueAsVector ( BlackboardKeys::chTargetLocation ) , actualMovementSpeed ) );
                //GEngine->AddOnScreenDebugMessage ( -1 , 3.0f , FColor::Red , FString::Printf ( TEXT ( "Increase Speed: %f" ) , actualMovementSpeed ) );
            }
            //GEngine->AddOnScreenDebugMessage ( -1 , 3.0f , FColor::Red , FString::Printf ( TEXT ( "Dist: %f" ) , Distance ) );

            //AddForceToMove ( GetActorLocation ( ) , controller->GetBlackboard ( )->GetValueAsVector ( BlackboardKeys::chTargetLocation ) , m_fMovementSpeed );
        }
    }
}

// Called to bind functionality to input
void AEnemyCorrupter::SetupPlayerInputComponent ( UInputComponent* PlayerInputComponent )
{
    Super::SetupPlayerInputComponent ( PlayerInputComponent );
}

// Spawn a Projectile
// [Deprecated]
void AEnemyCorrupter::Attack ( )
{
    if ( m_World != NULL )
    {
        // Get Bone Location as spawn point
        FVector boneLocation = this->GetMesh ( )->GetBoneLocation ( m_sBoneName , EBoneSpaces::Type::WorldSpace );
        m_vSpawnRoatation = GetControlRotation ( );
        m_vSpawnLocation = boneLocation + m_vSpawnLocationOffset;

        //GEngine->AddOnScreenDebugMessage ( -1 , 10.0f , FColor::Blue , FString::Printf ( TEXT ( "Bone: %s" ) , *( boneLocation.ToString ( ) ) ) );

        // Spawn Projectile
        FActorSpawnParameters actorSpawnParams;
        actorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

        m_World->SpawnActor<ACorrupterProjectile> ( m_pcTProjectile , m_vSpawnLocation , m_vSpawnRoatation , actorSpawnParams );

        // Set Blackboard key chPlayerAnimationAttack to false
        ACorrupterAIController* const controller = Cast<ACorrupterAIController> ( this->GetOwner ( ) );
        controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chPlayerAnimationAttack , false );
        controller->GetBlackboard ( )->SetValueAsBool ( BlackboardKeys::chAttackTarget , false );

        // Set The Combat Manager Can Attack to false
    }
}

// Explode the Actor on contact with player
void AEnemyCorrupter::Explode ( )
{
    // Get mesh component and World
    USkeletalMeshComponent* const mesh = GetMesh ( );
    UWorld* world = GetWorld ( );

    // Spaw particle effect on blast
    UGameplayStatics::SpawnEmitterAtLocation ( world , m_BlastVFX , mesh->GetComponentLocation ( ) , FRotator::ZeroRotator , FVector::OneVector , true , EPSCPoolMethod::AutoRelease , true );

    // Add impulse to the surrounding objects
    m_RadialForceComponent->FireImpulse ( );

    // Play SFX
    UGameplayStatics::PlaySoundAtLocation ( world , m_BlastSFX , mesh->GetComponentLocation ( ) , 1.0f , 1.0f , 0.0f );

    // Get Actor Surrounding a sphere
    FCollisionShape collisionSphere = FCollisionShape::MakeSphere ( m_fExplosionRadius );

    // Ignore Self
    TArray<AActor*> actorsToIgnore;
    actorsToIgnore.Add ( this );

    TArray<AActor*> OutActors;
    const TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
    TArray<UPrimitiveComponent*> OverlapComponents;

    // Check collision for Player
    UClass* ActorClassFilter = APlayerCharacter::StaticClass ( );

    // Overlap Sphere
    bool bOverlapped = UKismetSystemLibrary::SphereOverlapActors ( world , GetActorLocation ( ) , collisionSphere.GetSphereRadius ( ) , ObjectTypes , ActorClassFilter , actorsToIgnore , OutActors );
    //DrawDebugSphere ( GetWorld ( ) , GetActorLocation ( ) , collisionSphere.GetSphereRadius ( ) , 20 , FColor::Red , false , 3.2f );

    // Damage the player if overlapping
    if ( bOverlapped )
    {
        APlayerController* const playerController = Cast<APlayerController> ( UGameplayStatics::GetPlayerController ( GetWorld ( ) , 0 ) );
        APlayerCharacter* const playerCharacter = Cast<APlayerCharacter> ( playerController->GetCharacter ( ) );
        UGameplayStatics::ApplyDamage ( playerCharacter , m_fDamageAmount , playerController , this , UDamageType::StaticClass ( ) );
    }

    // Kill the Enemy
    Die ( false );
}

//Check Collisions
void AEnemyCorrupter::OnHit ( UPrimitiveComponent* HitComp , AActor* OtherActor , UPrimitiveComponent* OtherComp , FVector NormalImpulse , const FHitResult& Hit )
{
    if ( ( OtherActor != NULL ) && ( OtherActor != this ) && ( OtherComp != NULL ) )
    {
        APlayerController* const playerController = Cast<APlayerController> ( UGameplayStatics::GetPlayerController ( GetWorld ( ) , 0 ) );

        if ( ( OtherActor != this ) && OtherActor == Cast<ACharacter> ( playerController->GetCharacter ( ) ) )
        {
            // Kill self and damage player
            Explode ( );
        }

        // Bullet Hit of Player NOTE: Is not being detected because bullets are lerping and collisions are off
        /*
        {
            if ( ( OtherActor != this ) && OtherActor->IsA<AProjectile> ( ) )
            {
                // Spaw particle effect on blast
                UGameplayStatics::SpawnEmitterAtLocation ( GetWorld() , m_BulletHitVFX , Hit.Normal , FRotator::ZeroRotator , FVector::OneVector , true , EPSCPoolMethod::AutoRelease , true );

                // Play SFX
                UGameplayStatics::PlaySoundAtLocation ( GetWorld ( ) , m_BulletHitSFX , Hit.Location , 1.0f , 1.0f , 0.0f );
            }
        }
        */

    }
}

// Damage sequence when enemy gets attacked
float AEnemyCorrupter::TakeDamage ( float DamageAmount , FDamageEvent const& DamageEvent , AController* EventInstigator , AActor* DamageCauser )
{
    // Spaw particle effect on blast
    UGameplayStatics::SpawnEmitterAtLocation ( GetWorld ( ) , m_BulletHitVFX , GetActorLocation ( ) , FRotator::ZeroRotator , FVector::OneVector , true , EPSCPoolMethod::AutoRelease , true );

    // Play SFX
    UGameplayStatics::PlaySoundAtLocation ( GetWorld ( ) , m_BulletHitSFX , GetActorLocation ( ) , 1.0f , 1.0f , 0.0f );

    // Broadcast Take Damage
    TakeHitDamage.Broadcast ( DamageAmount );

    // Substract Health 
    m_fCurrentHealth -= DamageAmount;

    // Enemy Die
    if ( m_fCurrentHealth <= 0 )
    {
        Explode ( );
        //Die ( false );
    }

    return m_fCurrentHealth;
}

// Returns Current Health Percentage
float AEnemyCorrupter::GetHealthBarPercentage ( ) const
{
    return m_fCurrentHealth / m_fInitialHealth;
}

FVector AEnemyCorrupter::MoveTowardsLocation ( FVector v3Current , FVector v3Target , float fMaxDistanceDelta )
{
    // Get the target position.
    FVector TargetPos = v3Target - v3Current;

    // Delta to move at constant speed.
    float Delta = fMaxDistanceDelta * m_fDeltaTime;

    // Distance between two points.
    float Distance = TargetPos.Size ( );

    if ( Distance <= Delta || Distance == 0.f )
    {
        return v3Target;
    }

    // Return the new position after applying the target position.
    return v3Current + TargetPos / Distance * Delta;
}

void AEnemyCorrupter::AddForceToMove ( FVector v3Current , FVector v3Target , float fMaxDistanceDelta )
{
    // Calculating the direction from start to end point
    FVector direction = UKismetMathLibrary::GetDirectionUnitVector ( v3Current , v3Target );

    // Adding force on the capsule component
    m_CapsuleComponent->AddForce ( direction * m_CapsuleComponent->GetMass ( ) * fMaxDistanceDelta );

    // Get Character Movement Component of AI
    UCharacterMovementComponent* const CharacterMovementVeclocity = Cast<UCharacterMovementComponent> ( GetCharacterMovement ( ) );

    // Direction Unit Vector between npc and actualLocation
    //FVector direction = UKismetMathLibrary::GetDirectionUnitVector ( v3Current , v3Target );
    // Caluculate actual velocity
    //FVector velocity = direction * fMaxDistanceDelta;

    // Set Velocity
    //CharacterMovementVeclocity->Velocity = velocity;
}

