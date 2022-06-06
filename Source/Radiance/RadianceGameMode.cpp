// Copyright Epic Games, Inc. All Rights Reserved.

#include "RadianceGameMode.h"
#include "RadianceCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include <Kismet/GameplayStatics.h>
#include "RadianceGameInstance.h"

ARadianceGameMode::ARadianceGameMode()
{
	// Set default pawn class to our Blueprinted characte
	// Changed the player reference to use the correct player (Nikodem Hamrol).
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Radiance/Player/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

void ARadianceGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Create an instance of the game instance in order to load the save game file (Nikodem Hamrol).
	URadianceGameInstance* GameInstance = Cast<URadianceGameInstance>( UGameplayStatics::GetGameInstance( GetWorld() ) );

	// Check if the save game file exists
	GameInstance->CheckIfSaveGameExists();
}
