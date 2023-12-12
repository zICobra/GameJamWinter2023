// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToolBase.h"
#include "A_Broom.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAMWINTER2023_API AA_Broom : public AToolBase
{
	GENERATED_BODY()

	virtual void ActivateTool() override;
	virtual void DeactivateTool() override;
	virtual void InteractWithInteractable(class AInteractableBase* Interactable);
	virtual bool IsCompatibleWithInteractable(class AInteractableBase* Interactable) override;

	UPROPERTY(EditDefaultsOnly, Category = "Tools")
	class UDA_InteractableAllowed* ToolData;
	
};
