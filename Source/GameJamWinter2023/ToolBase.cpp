// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolBase.h"

#include "InteractableBase.h"
#include "DA_InteractableAllowed.h"

// Sets default values
AToolBase::AToolBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AToolBase::ActivateTool()
{
	UE_LOG(LogTemp, Warning, TEXT("Activate"));
}

void AToolBase::DeactivateTool()
{
	UE_LOG(LogTemp, Warning, TEXT("Deactivate"));
}

void AToolBase::InteractWithInteractable(AInteractableBase* Interactable)
{
	
}

bool AToolBase::IsCompatibleWithInteractable(AInteractableBase* Interactable)
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

// Called when the game starts or when spawned
void AToolBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToolBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

