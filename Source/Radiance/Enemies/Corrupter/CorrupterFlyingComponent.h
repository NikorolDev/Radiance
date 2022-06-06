// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyCorrupter.h"
#include "CorrupterFlyingComponent.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UCorrupterFlyingComponent
// Author				: Saurya Saurav
// Editors				: 
// Classes Inherited	: UActorComponent
// Purpose				: Enemy Actor Component to Play Fly Sound
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API UCorrupterFlyingComponent : public UActorComponent
{
	GENERATED_BODY ( )

public:

    // Sets default values for this component's properties
    UCorrupterFlyingComponent ( );

    // Called every frame
    virtual void TickComponent ( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

    UFUNCTION ( )
        void DestroySound ( );

protected:

    // Called when the game starts
    virtual void BeginPlay ( ) override;

    // Flying SFX to play
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Flying Properties" ,
                meta = ( DisplayName = "Flying Movement SFX" , ToolTip = "SFX for Enemy Flying" ) )
        USoundBase* m_FlyingSFX;
		
    // Flying SFX to play
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Flying Properties" ,
                meta = ( DisplayName = "Attacking Movement SFX" , ToolTip = "SFX for Attacking Flying" ) )
        USoundBase* m_AttackingSFX;

    // Flying Attenation
    UPROPERTY ( EditAnywhere , BlueprintReadWrite , Category = "Enemy Flying Properties" ,
                meta = ( DisplayName = "Flying Attenuation SFX" , ToolTip = "Attenuation for Enemy Flying" ) )
        USoundAttenuation* m_FlyingAttenuation;

    UPROPERTY()
        UAudioComponent* m_FlyingAudioComponent;
    
    UPROPERTY()
        UAudioComponent* m_AttackingAudioComponent;

private:

    UPROPERTY ( )
        AEnemyCorrupter* m_pcNPC;

    bool init;

};
