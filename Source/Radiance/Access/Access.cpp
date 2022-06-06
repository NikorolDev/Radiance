// Fill out your copyright notice in the Description page of Project Settings.


#include "Access.h"
#include "Radiance/Puzzle/Slot.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Radiance/Inventory/InventoryManager.h"

AAccess::AAccess() 
{

}

void AAccess::ModuleAttached()
{

}

void AAccess::ModuleDetached()
{
	// Lock access as a module has been detached.
	m_bLocked = true;

	// Change the light to red to indicate it is locked.
	Light->SetLightColor(FLinearColor::Red);

	// Close access.
	m_Timeline.Reverse();

	if (Blocker)
	{
		Blocker->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

bool AAccess::CheckModuleCount()
{
	// Reset the current modules, ready to count the total active.
	int m_iCurrentModules = 0;
	if (Modules.Num() > 0)
	{
		for (ASlot* i : Modules)
		{
			// Checks to see if the module is active.
			if (i->CheckForModule())
			{
				m_iCurrentModules++;

				// If all modules are active then return true.
				if (m_iCurrentModules == Modules.Num())
				{
						// Get the inventory manager that is in the level.
						m_pcInventoryManager = Cast<AInventoryManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AInventoryManager::StaticClass()));

						m_pcInventoryManager->AddItem(m_sObjectiveID, 1);

						// Play charged audio sound to indicate to player that they have taken damage.
						UGameplayStatics::PlaySound2D(GetWorld(), AccessGrantedSFX, 1);

					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("OPEN."));
					return true;
				}
			}
			else
			{
				// Play charged audio sound to indicate to player that they have taken damage.
				UGameplayStatics::PlaySound2D(GetWorld(), AccessDeniedSFX, 1);
				// Not enough modules to allow access.
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("NOT ENOUGH MODULES TO OPEN ACCESS."));
				return false;
			}
		}
	}
	else
	{
		return true;
	}
	return false;
}

void AAccess::TerminalActivated()
{

}
