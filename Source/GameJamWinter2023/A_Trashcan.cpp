// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Trashcan.h"

#include "InteractableBase.h"
#include "DA_InteractableAllowed.h"

void AA_Trashcan::ActivateTool()
{
    if(TrashcanBlueprint)
	{
    	GetWorld()->SpawnActor<AActor>(TrashcanBlueprint->GeneratedClass, FVector::ZeroVector, FRotator::ZeroRotator);
	}
}

void AA_Trashcan::DeactivateTool()
{
    DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
}

void AA_Trashcan::InteractWithInteractable(class AInteractableBase* Interactable)
{
    Interactable->Destroy();
}

bool AA_Trashcan::IsCompatibleWithInteractable(class AInteractableBase* Interactable)
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
