// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToolBase.generated.h"

UCLASS()
class GAMEJAMWINTER2023_API AToolBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AToolBase();

	virtual void ActivateTool();
	virtual void DeactivateTool();
	virtual void InteractWithInteractable(class AInteractableBase* Interactable);
	virtual bool IsCompatibleWithInteractable(class AInteractableBase* Interactable);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UDA_InteractableAllowed* ToolData;

};


