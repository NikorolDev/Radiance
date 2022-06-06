// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointSaveGame.h"

UCheckpointSaveGame::UCheckpointSaveGame()
{
    m_cPlayerName = TEXT("TestSaveSlot");
    m_v3PlayerLocation = FVector( 0, 0, 0 );
}

/*
if (UCheckpointSaveGame* SaveGameInstance = Cast<UCheckpointSaveGame>(UGameplayStatics::CreateSaveGameObject(UCheckpointSaveGame::StaticClass())))
{
// Set up the (optional) delegate.
FAsyncSaveGameToSlotDelegate SavedDelegate;
// USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
SavedDelegate.BindUObject(SomeUObjectPointer, &USomeUObjectClass::SaveGameDelegateFunction);

// Set data on the savegame object.
SaveGameInstance->PlayerName = TEXT("PlayerOne");

// Start async save process.
UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SlotNameString, UserIndexInt32, SavedDelegate);
}
*/

