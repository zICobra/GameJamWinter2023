// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Wand.h"

#include "InteractableBase.h"
#include "DA_InteractableAllowed.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


void AA_Wand::ActivateTool()
{
    if(WandBlueprint)
	{
    	GetWorld()->SpawnActor<AActor>(WandBlueprint->GeneratedClass, FVector::ZeroVector, FRotator::ZeroRotator);
	}
			
}

void AA_Wand::DeactivateTool()
{
	DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
}

void AA_Wand::InteractWithInteractable(class AInteractableBase* Interactable)
{
	Interactable->StartInteract();
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WandSound, GetActorLocation(), WandSound->GetVolumeMultiplier(), WandSound->GetPitchMultiplier());
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


