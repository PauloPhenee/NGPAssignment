// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SkaterController.generated.h"

class UInputAction;
class UInputMappingContext;
class USkaterMovementComponent;

UCLASS()
class NGP_API ASkaterController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> IMC_Skate;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Steer;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Jump;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

protected:
	// Input handlers
	void OnSteerTriggered(const struct FInputActionValue& Value);
	void OnSteerCompleted(const struct FInputActionValue& Value);
	void OnMoveTriggered(const struct FInputActionValue& Value);
	void OnMoveCompleted(const struct FInputActionValue& Value);
	void OnJumpTriggered(const struct FInputActionValue& Value);


	USkaterMovementComponent* MovementComponent;
};
