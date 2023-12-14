// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ToolBase.h"
#include "C_FirstPersonCharacter.generated.h"

UCLASS()
class GAMEJAMWINTER2023_API AC_FirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_FirstPersonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UDA_InputConfig* InputActions;

	UFUNCTION(BlueprintImplementableEvent)
	void CameraAnimation();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float HeadMovementIntensity = 1.5;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* WandSpawn;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BroomSpawn;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* TrashcanSpawn;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CallPauseMenu();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SwitchTool(int32 ToolIndex);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void TurnEagleVisionOn();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void TurnEagleVisionOff();

	class AToolBase* CurrentTool;

	UPROPERTY(BlueprintReadWrite)
	bool IsEagleVisionOn = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	float MouseSensitivity = 0.75;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	float ControllerSensitivity = 0.75;

	void SwitchToNextTool();
	void SwitchToPreviousTool(); 
private:

	void Move(const FInputActionValue& Value);
	void StartSprinting();
	void StopSprinting();
	void ControllerSprint();

	void Look(const FInputActionValue& Value);
	void ControllerLook(const FInputActionValue& Value);

	void StartJumping();
	void ReleaseJumping();

	void Interact();

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundCue* KellerFootsteps;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundCue* HolzbodenFootsteps;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	class USoundCue* DachbodenFootsteps;

	UFUNCTION(BlueprintCallable)
	void Footsteps();




	UPROPERTY(EditAnywhere, Category = "Speed")
	float NormalWalkSpeed = 700;
	UPROPERTY(EditAnywhere, Category = "Speed")
	float SprintSpeed = 1500;
	UPROPERTY(EditDefaultsOnly, Category = "MovementCapabillities")
	bool CanSprint = true;
	UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();

	AActor* HitActor;
	bool Grabbed = false;
	AActor* GrabbedActor;

	class UPhysicsHandleComponent* GetPhysicsHandle();

	UPROPERTY(EditAnywhere, Category = "Interactable")
	float InteractableRange = 1000;
	UPROPERTY(EditAnywhere, Category = "Interactable")
	float GrabDistance = 200;

	FVector StartPoint;
	FRotator PlayerRotation;
	FVector EndPoint;
	FVector TargetPoint;

	class AInteractableBase* PreviouslyHitActor;

	UPROPERTY(EditAnywhere, Category = "Tools")
	TArray<TSubclassOf<AToolBase>> ToolClasses;
	
	TArray<USceneComponent*> ToolAttachmentPoints;

	TArray<AToolBase*> Tools;
	int32 CurrentToolIndex;


};
