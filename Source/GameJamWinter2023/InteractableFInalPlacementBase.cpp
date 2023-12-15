// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableFInalPlacementBase.h"

#include "InteractableBase.h"
#include "DA_PlacementInfo.h"

void AInteractableFInalPlacementBase::Interacted(AInteractableBase* Interactable)
{
    if(IsHoldingCorrectInteractable(Interactable))
    {
        for (UDA_PlacementInfo* PlacementInfo : InteractablePlacementInfoArray)
        {
        if (PlacementInfo->InteractableClass == GetClass())
            {
                 PlacementInfo->AssociatedStaticMesh->SetVisibility(true);
                 break;
            }
        }
    }
}

bool AInteractableFInalPlacementBase::IsHoldingCorrectInteractable(AInteractableBase* Interactable)
{
    if (InteractableBlueprint && InteractableBlueprint->IsA<UBlueprint>())
    {
        UBlueprint* TargetBlueprint = Cast<UBlueprint>(InteractableBlueprint);

        return Interactable->GetClass() == TargetBlueprint->GeneratedClass;
    }

    return false;
}

