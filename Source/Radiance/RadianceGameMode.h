// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RadianceGameMode.generated.h"

UCLASS(minimalapi)
class ARadianceGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARadianceGameMode();

#pragma region Inventory
protected:
	virtual void BeginPlay() override;

#pragma endregion


};



