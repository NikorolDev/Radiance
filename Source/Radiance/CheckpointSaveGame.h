// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CheckpointSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class RADIANCE_API UCheckpointSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	// Setting player name as a UProperty in PLayer Ssve category
	UPROPERTY(VisibleAnywhere, Category = "Player Save")
		FString m_cPlayerName;

	// Setting player location as a UProperty in PLayer Ssve category
	UPROPERTY(VisibleAnywhere, Category = "Player Save")
		FVector m_v3PlayerLocation;

	UCheckpointSaveGame ( );
};
