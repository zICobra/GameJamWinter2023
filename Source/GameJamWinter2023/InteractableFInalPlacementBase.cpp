// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableFInalPlacementBase.h"

#include"InteractableBase.h"

void AInteractableFInalPlacementBase::Interacted(AInteractableBase* Interactable)
{
    if(IsHoldingCorrectInteractable(Interactable))
    {
        UE_LOG(LogTemp, Warning, TEXT("Interacted"));
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

