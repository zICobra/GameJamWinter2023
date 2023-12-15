// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToolBase.h"
#include "A_Trashcan.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAMWINTER2023_API AA_Trashcan : public AToolBase
{
	GENERATED_BODY()

public:
	virtual void ActivateTool() override;
	virtual void DeactivateTool() override;
	virtual void InteractWithInteractable(class AInteractableBase* Interactable);
	virtual bool IsCompatibleWithInteractable(class AInteractableBase* Interactable) override;


	UPROPERTY(EditDefaultsOnly, Category = "Tools")
	class UDA_InteractableAllowed* ToolData;
	UPROPERTY(EditAnywhere, Category = "Tools")
	UBlueprint* TrashcanBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundCue* TrashcanSound;
	
};
