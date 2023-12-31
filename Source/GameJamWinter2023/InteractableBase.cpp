// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBase.h"

#include "Components/TextRenderComponent.h"
#include "Engine/TargetPoint.h"

// Sets default values
AInteractableBase::AInteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AInteractableBase::SpawnInteractables()
{
    if(SpawnLocations.Num() == 0)
    {
        SpawnLocation = GetActorLocation();
        return;
    }
    int32 RandomIndex = FMath::RandRange(0, SpawnLocations.Num() - 1);

    RandomLocation = SpawnLocations[RandomIndex];

    SpawnLocation = RandomLocation->GetActorLocation();

    if(InteractableBlueprint)
    {
        GetWorld()->SpawnActor<AActor>(InteractableBlueprint->GeneratedClass, RandomLocation->GetActorLocation(), RandomLocation->GetActorRotation());
    }

}

void AInteractableBase::RespawnActor()
{
    Destroy();
}

void AInteractableBase::Outline(USceneComponent* Component)
{

    if (Component)
    {
        UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Component);
        if(StaticMeshComponent)
        {
            StaticMeshComponent->SetRenderCustomDepth(true);
            return;
        }
    }
}

void AInteractableBase::ClearOutline(USceneComponent* Component)
{

    if (Component)
    {
        UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Component);
        if(StaticMeshComponent)
        {
            StaticMeshComponent->SetRenderCustomDepth(false);
            return;
        }
    }
}


// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();

    SpawnInteractables();
	
}

// Called every frame
void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

