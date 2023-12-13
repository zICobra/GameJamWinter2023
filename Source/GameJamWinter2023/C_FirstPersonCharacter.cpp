// Fill out your copyright notice in the Description page of Project Settings.


#include "C_FirstPersonCharacter.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "DA_InputConfig.h"
#include "InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "InteractableBase.h"
#include "A_Wand.h"

// Sets default values
AC_FirstPersonCharacter::AC_FirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	WandSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("WandSpawn"));
	BroomSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("BroomSpawn"));
	TrashcanSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("TrashcanSpawn"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	WandSpawn->SetupAttachment(RootComponent);
	BroomSpawn->SetupAttachment(RootComponent);
	TrashcanSpawn->SetupAttachment(RootComponent);



}

// Called when the game starts or when spawned
void AC_FirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (CharacterMovement)
	{
		CharacterMovement->MaxWalkSpeed = NormalWalkSpeed;
	}
	CameraAnimation();

	ToolAttachmentPoints.Add(WandSpawn);
	ToolAttachmentPoints.Add(BroomSpawn);
	ToolAttachmentPoints.Add(TrashcanSpawn);

	for (TSubclassOf<AToolBase>& ToolClass : ToolClasses)
    {
        AToolBase* Tool = GetWorld()->SpawnActor<AToolBase>(ToolClass, FVector::ZeroVector, FRotator::ZeroRotator);
        Tools.Add(Tool);
    }

    Tools[CurrentToolIndex]->ActivateTool();
	Tools[CurrentToolIndex]->AttachToComponent(ToolAttachmentPoints[CurrentToolIndex], FAttachmentTransformRules::SnapToTargetIncludingScale);
}

// Called every frame
void AC_FirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Controller->GetPlayerViewPoint(StartPoint, PlayerRotation);
	EndPoint = StartPoint + PlayerRotation.Vector() * InteractableRange;

	FHitResult HitResult;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	if(Grabbed)
	{
		FVector TargetLocation = Camera->GetComponentLocation() + Camera->GetForwardVector() * 500;
		UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
		PhysicsHandle->SetTargetLocation(TargetLocation);
		return;
	}


	bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_GameTraceChannel1, Params);

	if (HitResult.GetActor() != PreviouslyHitActor)
    {
        if (PreviouslyHitActor)
        {
            PreviouslyHitActor->ClearOutline(PreviouslyHitActor->FindComponentByClass<UStaticMeshComponent>());
        }

        if (bSuccess && HitResult.GetActor())
        {
            PreviouslyHitActor = Cast<AInteractableBase>(HitResult.GetActor());

			PreviouslyHitActor->Outline(HitResult.GetActor()->FindComponentByClass<UStaticMeshComponent>());
        }
        else
        {
            PreviouslyHitActor = nullptr;
			
        }
    }
}

// Called to bind functionality to input
void AC_FirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PC = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	PEI->BindAction(InputActions->InputMove, ETriggerEvent::Triggered, this, &AC_FirstPersonCharacter::Move);
	PEI->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &AC_FirstPersonCharacter::Look);
	PEI->BindAction(InputActions->InputControllerLook, ETriggerEvent::Triggered, this, &AC_FirstPersonCharacter::ControllerLook);
	PEI->BindAction(InputActions->InputPauseMenu, ETriggerEvent::Started, this, &AC_FirstPersonCharacter::CallPauseMenu);
	PEI->BindAction(InputActions->InputInteract, ETriggerEvent::Started, this, &AC_FirstPersonCharacter::Interact);
	PEI->BindAction(InputActions->InputNextTool, ETriggerEvent::Started, this, &AC_FirstPersonCharacter::SwitchToNextTool);
	PEI->BindAction(InputActions->InputPreviousTool, ETriggerEvent::Started, this, &AC_FirstPersonCharacter::SwitchToPreviousTool);
	if(CanSprint)
	{
		PEI->BindAction(InputActions->InputKeyboardSprint, ETriggerEvent::Started, this, &AC_FirstPersonCharacter::StartSprinting);
		PEI->BindAction(InputActions->InputKeyboardSprint, ETriggerEvent::Completed, this, &AC_FirstPersonCharacter::StopSprinting);
		PEI->BindAction(InputActions->InputControllerSprint, ETriggerEvent::Started, this, &AC_FirstPersonCharacter::ControllerSprint);
	}
	PEI->BindAction(InputActions->InputJump, ETriggerEvent::Started, this, &AC_FirstPersonCharacter::StartJumping);
	PEI->BindAction(InputActions->InputJump, ETriggerEvent::Completed, this, &AC_FirstPersonCharacter::ReleaseJumping);
	
}	



void AC_FirstPersonCharacter::Move(const FInputActionValue& Value)
{
	if(Controller)
	{
		const FVector2D MoveValue = Value.Get<FVector2D>();
		const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);
		
		//Forward/Backward direction
		if(MoveValue.Y != 0)
		{
			//Get forward vector
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);
			AddMovementInput(Direction, MoveValue.Y);
		}

		//Right/Left direction 
		if(MoveValue.X != 0)
		{
			//Get right vector
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

			AddMovementInput(Direction, MoveValue.X);
		}
	}
}

void AC_FirstPersonCharacter::StartSprinting()
{
	if (CharacterMovement)
	{
		CharacterMovement->MaxWalkSpeed = SprintSpeed;
	}
}

void AC_FirstPersonCharacter::StopSprinting()
{
	if (CharacterMovement)
	{
		CharacterMovement->MaxWalkSpeed = NormalWalkSpeed;
	}
}

void AC_FirstPersonCharacter::ControllerSprint()
{
	if (CharacterMovement)
	{
		if(CharacterMovement->MaxWalkSpeed == SprintSpeed)
		{
			CharacterMovement->MaxWalkSpeed = NormalWalkSpeed;
			return;
		}

		CharacterMovement->MaxWalkSpeed = SprintSpeed;
	}
}

void AC_FirstPersonCharacter::Look(const FInputActionValue& Value)
{
	if(Controller)
	{
		const FVector2D LookValue = Value.Get<FVector2D>();
		
		if(LookValue.X != 0)
		{
			AddControllerYawInput(LookValue.X * MouseSensitivity);
		}

		if(LookValue.Y != 0)
		{
			AddControllerPitchInput(-LookValue.Y * MouseSensitivity);
		}
	}
}

void AC_FirstPersonCharacter::ControllerLook(const FInputActionValue& Value)
{
	if(Controller)
	{
		const FVector2D LookValue = Value.Get<FVector2D>();
		
		if(LookValue.X != 0)
		{
			AddControllerYawInput(LookValue.X * ControllerSensitivity);
		}

		if(LookValue.Y != 0)
		{
			AddControllerPitchInput(LookValue.Y * ControllerSensitivity);
		}
	}
}

void AC_FirstPersonCharacter::StartJumping()
{
	Jump();
}

void AC_FirstPersonCharacter::ReleaseJumping()
{
	StopJumping();
}

void AC_FirstPersonCharacter::Interact()
{
	if(Grabbed == true)
	{
		Grabbed = false;
		AInteractableBase* InteractionBase = Cast<AInteractableBase>(HitActor);
		UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
		PhysicsHandle->ReleaseComponent();
		InteractionBase->StopInteract();
		return;
		
	}
	
	Controller->GetPlayerViewPoint(StartPoint, PlayerRotation);
	EndPoint = StartPoint + PlayerRotation.Vector() * InteractableRange;
	TargetPoint = StartPoint + PlayerRotation.Vector() * GrabDistance;

	FHitResult HitResult;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());


	bool bSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_GameTraceChannel1, Params);

	if(bSuccess && HitResult.GetActor())
	{	
		HitActor = HitResult.GetActor();
		if(HitActor && HitActor->IsA<AInteractableBase>())
		{
			if(Tools[CurrentToolIndex])
			{
				AInteractableBase* Interactable = Cast<AInteractableBase>(HitActor);
				if(Interactable && Tools[CurrentToolIndex]->IsCompatibleWithInteractable(Interactable))
				{
					Tools[CurrentToolIndex]->InteractWithInteractable(Interactable);
					if(Tools[CurrentToolIndex]->IsA<AA_Wand>())
					{
						Grabbed = true;
						UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
						HitResult.GetComponent()->SetSimulatePhysics(true);
						PhysicsHandle->GrabComponentAtLocationWithRotation(HitResult.GetComponent(), NAME_None, HitResult.ImpactPoint, HitResult.GetActor()->GetActorRotation());
					}
				}
			}
				
		}
	}
}


class UPhysicsHandleComponent* AC_FirstPersonCharacter::GetPhysicsHandle()
{
	UPhysicsHandleComponent* Result = FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("requires a PhysicsHandle!"));
	}
	return Result;
}


void AC_FirstPersonCharacter::SwitchToNextTool()
{	
	Tools[CurrentToolIndex]->DeactivateTool();
	CurrentToolIndex = (CurrentToolIndex + 1) % Tools.Num();
	Tools[CurrentToolIndex]->ActivateTool();
	Tools[CurrentToolIndex]->AttachToComponent(ToolAttachmentPoints[CurrentToolIndex], FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void AC_FirstPersonCharacter::SwitchToPreviousTool()
{
	Tools[CurrentToolIndex]->DeactivateTool();
	CurrentToolIndex = (CurrentToolIndex - 1 + Tools.Num()) % Tools.Num();
	Tools[CurrentToolIndex]->ActivateTool();
	Tools[CurrentToolIndex]->AttachToComponent(ToolAttachmentPoints[CurrentToolIndex], FAttachmentTransformRules::SnapToTargetIncludingScale);
}