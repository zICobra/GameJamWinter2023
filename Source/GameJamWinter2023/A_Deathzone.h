// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_Deathzone.generated.h"

UCLASS()
class GAMEJAMWINTER2023_API AA_Deathzone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_Deathzone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Deathzone;

	UFUNCTION(BlueprintCallable)
	void OverlapDeathzone(AActor* OtherActor);

};
