// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Wand.h"

#include "InteractableBase.h"
#include "DA_InteractableAllowed.h"


void AA_Wand::ActivateTool()
{
    GetWorld()->SpawnActor<AA_Wand>(FVector::ZeroVector, FRotator::ZeroRotator);
    UE_LOG(LogTemp, Warning, TEXT("Spawning Wand"));
}

void AA_Wand::DeactivateTool()
{
    Destroy();
}

void AA_Wand::InteractWithInteractable(class AInteractableBase* Interactable)
{
    if (IsCompatibleWithInteractable(Interactable))
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractWithInteractable"));
	}
}

bool AA_Wand::IsCompatibleWithInteractable(class AInteractableBase* Interactable)
{
    if(!ToolData)
	{
		return false;
	}
	for (const auto& AllowedInteractableType : ToolData->AllowedInteractables)
	{
		if(Interactable->IsA(AllowedInteractableType))
		{
			UE_LOG(LogTemp, Warning, TEXT("AllowedInteractable"));
			return true;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("WrongInteractable"));
	return false;
}

