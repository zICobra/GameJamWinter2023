// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Broom.h"

#include "InteractableBase.h"
#include "DA_InteractableAllowed.h"

void AA_Broom::ActivateTool()
{
	if(BroomBlueprint)
	{
    	GetWorld()->SpawnActor<AActor>(BroomBlueprint->GeneratedClass, FVector::ZeroVector, FRotator::ZeroRotator);
	}
}

void AA_Broom::DeactivateTool()
{
	DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
}

void AA_Broom::InteractWithInteractable(class AInteractableBase* Interactable)
{
	Interactable->Destroy();
}

bool AA_Broom::IsCompatibleWithInteractable(class AInteractableBase* Interactable)
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
