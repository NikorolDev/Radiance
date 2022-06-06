// Fill out your copyright notice in the Description page of Project Settings.


#include "Motion.h"

// Sets default values
AMotion::AMotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMotion::BeginPlay()
{
	Super::BeginPlay();

	// Checks for the animation curve.
	if (AnimationCurve)
	{
		// Get the required timeline properties.
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		// Bind the 'MotionHandler' function as the function to call when the timeline is in play.
		TimelineCallback.BindUFunction(this, FName("MotionHandler"));

		// Bind the 'MotionFinished' function when the timeline is finished.
		TimelineFinishedCallback.BindUFunction(this, FName{ TEXT("MotionFinished") });

		// Allow the animation curve specified to interact with the timeline.
		m_Timeline.AddInterpFloat(AnimationCurve, TimelineCallback);

		// Assign the timeline finished function to the callback assigned above.
		m_Timeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	}
}

FTimeline* AMotion::GetTimeline()
{
	return &m_Timeline;
}

// Called every frame
void AMotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Tick the timeline.
	m_Timeline.TickTimeline(DeltaTime);
}

void AMotion::MotionHandler()
{

}

void AMotion::MotionFinished()
{

}

