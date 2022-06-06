// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_Base.h"

#include "Components/BoxComponent.h"

ATriggerVolume_Base::ATriggerVolume_Base()
{
	// Set this actor to not call Tick() every frame. This is because there is no need for a tick in this class
	// as it only creates the components.
	PrimaryActorTick.bCanEverTick = false;

	// Create and setup...
	// Box Component (m_BoxTriggerVolume).
	m_BoxTriggerVolume = CreateDefaultSubobject<UBoxComponent>( TEXT( "Box Trigger Volume" ) );
	m_BoxTriggerVolume->SetCollisionResponseToAllChannels( ECollisionResponse::ECR_Overlap );
	m_BoxTriggerVolume->SetCollisionEnabled( ECollisionEnabled::QueryOnly );
	m_BoxTriggerVolume->SetGenerateOverlapEvents( true );
	m_BoxTriggerVolume->SetBoxExtent( FVector( 50.0f ) );
	RootComponent = m_BoxTriggerVolume;

	// Static Mesh (m_VisualMesh).
	m_VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Visualiser" ) );

	// Find the cube that is in the engine content to apply the correct mesh to surround the box component.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset( TEXT( "/Engine/BasicShapes/Cube1.Cube1" ) );

	// Check if it was able to find the mesh.
	if( CubeAsset.Succeeded() )
	{
		// Apply the cube mesh, set collision response to ignore all and setup attachment to the box trigger volume.
		m_VisualMesh->SetStaticMesh( CubeAsset.Object );
		m_VisualMesh->SetCollisionResponseToAllChannels( ECollisionResponse::ECR_Ignore );
		m_VisualMesh->SetupAttachment( m_BoxTriggerVolume );
	}
}
