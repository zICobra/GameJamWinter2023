// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableBase.generated.h"

UCLASS()
class GAMEJAMWINTER2023_API AInteractableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableBase();

	void Outline(USceneComponent* Component);
	void ClearOutline(USceneComponent* Component);

	UFUNCTION(BlueprintImplementableEvent)
	void StartInteract();
	UFUNCTION(BlueprintImplementableEvent)
	void StopInteract();
	UFUNCTION(BlueprintCallable)
	void SpawnInteractables();
	UFUNCTION(BlueprintCallable)
	void RespawnActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPoints")
	TArray<class ATargetPoint*> SpawnLocations;
	
	UPROPERTY(EditDefaultsOnly, Category = "SpawnPoints")
	UBlueprint* InteractableBlueprint;

	FVector SpawnLocation;

	class ATargetPoint* RandomLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
