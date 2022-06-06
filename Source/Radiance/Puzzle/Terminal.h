// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Radiance/Items/Interactable.h"
#include "Terminal.generated.h"

class AAccess;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			:	ATerminal
// Author				:	Kurtis Watson
// Inherits				:	AActor - Inherited so it is able to be placed in the world.
//							IInteractable - Allows for a function to be called when the player interacts with the object. 
// Purpose				:	Used to active terminal doors when all modules are connected.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class RADIANCE_API ATerminal : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	//-----------------------------------------------------------------------------------------------------------------------------
	// Constructor name		:	ATerminal
	// Author				:	Kurtis Watson
	//-----------------------------------------------------------------------------------------------------------------------------
	ATerminal();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TerminalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TerminalButton;

	// The object to open with the terminal.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		TArray<AAccess*> Access;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: OnInteract
	// Author				: Gaetano Trovato
	// Parameters			: Caller - The actor who called the function
	// Purpose				: Signature of the function which allows an interaction with another actor
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void OnInteract(AActor* Caller);
	void OnInteract_Implementation(AActor* Caller) override;

protected:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	BeginPlay
	// Author				:	UE4
	// Purpose				:	Called at game begin.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

public:	
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		:	Tick
	// Author				:	UE4
	// Purpose				:	To allow for variables etc. to be initialised, specific to this class.
	// Parameters			:	DeltaTime - Calculates the time different between previous and current frame.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void Tick(float DeltaTime) override;
};
