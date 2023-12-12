// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolBase.h"

#include "InteractableBase.h"

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

void AToolBase::InteractWithInteractable(AInteractableBase Interactable)
{
	UE_LOG(LogTemp, Warning, TEXT("InteractWithInteractable"));
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

