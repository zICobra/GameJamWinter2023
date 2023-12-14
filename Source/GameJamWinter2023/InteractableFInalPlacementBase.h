// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "InteractableFInalPlacementBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAMWINTER2023_API AInteractableFInalPlacementBase : public AInteractableBase
{
	GENERATED_BODY()
	
public:
	void Interacted(class AInteractableBase* Interactable);
	bool IsHoldingCorrectInteractable(class AInteractableBase* Interactable);
};
