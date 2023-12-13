// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "DA_InputConfig.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAMWINTER2023_API UDA_InputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputMove;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputControllerLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputPauseMenu;
	UPROPERTY(EditdefaultsOnly, BlueprintReadOnly)
	UInputAction* InputInteract;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputNextTool;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputPreviousTool;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputKeyboardSprint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputControllerSprint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputJump;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputEagleVision;

};
