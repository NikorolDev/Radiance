// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Motion.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AMotion
// Author				: Kurtis Watson
// Classes Inherited	: AActor
// Purpose				: To allow for derived classes to have an animation timeline.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API AMotion : public AActor
{
	GENERATED_BODY()
	
public:	
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		:	AMotion
	// Author				:	Kurtis Watson
	//-----------------------------------------------------------------------------------------------------------------------------
	AMotion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The animation curve to attach to the timeline.
	UPROPERTY(EditAnywhere)
		UCurveFloat* AnimationCurve;

	// Timeline that handles the animation.
	FTimeline m_Timeline;

	// The necessary variables to allow for smooth animation.
	float m_fCurveFloatValue;
	float m_fTimelineValue;

public:	
	FTimeline* GetTimeline();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Tick
	// Author				:	UE4
	// Purpose				:	To allow for variables etc. to be initialised, specific to this class.
	// Parameters			:	DeltaTime - Calculates the time different between previous and current frame.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void Tick(float DeltaTime) override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	MotionHandler
	// Author				:	Kurtis Watson
	// Purpose				:	To handle the animations along a timeline.
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
	virtual void MotionHandler();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	MotionFinished
	// Author				:	Kurtis Watson
	// Purpose				:	Called when the timeline is finished.
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
	virtual void MotionFinished();
};
