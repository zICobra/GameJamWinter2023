// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Wand.h"

#include "InteractableBase.h"
#include "DA_InteractableAllowed.h"


void AA_Wand::ActivateTool()
{
    GetWorld()->SpawnActor<AA_Wand>(FVector::ZeroVector, FRotator::ZeroRotator);
			
}

void AA_Wand::DeactivateTool()
{
    Destroy();
}

void AA_Wand::InteractWithInteractable(class AInteractableBase* Interactable)
{
	Grabbed = true;
	Interactable->StartInteract();
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
			return true;
		}
	}
	return false;
}


