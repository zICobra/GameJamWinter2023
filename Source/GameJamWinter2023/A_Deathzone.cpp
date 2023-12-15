// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Deathzone.h"
#include "Components/BoxComponent.h"
#include "Engine/TargetPoint.h"
#include "InteractableBase.h"

// Sets default values
AA_Deathzone::AA_Deathzone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Deathzone = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColliderFront"));
	Deathzone->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AA_Deathzone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AA_Deathzone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AA_Deathzone::OverlapDeathzone(AActor* OtherActor)
{
	if(OtherActor->IsA<AInteractableBase>())
	{
		AInteractableBase* Interactable = Cast<AInteractableBase>(OtherActor);
		Interactable->RespawnActor();
	}
}

