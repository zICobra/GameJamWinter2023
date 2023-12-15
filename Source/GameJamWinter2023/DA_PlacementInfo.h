// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_PlacementInfo.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAMWINTER2023_API UDA_PlacementInfo : public UDataAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
    TSubclassOf<class AInteractableBase> InteractableClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interactable")
    UStaticMeshComponent* AssociatedStaticMesh;

	
};
