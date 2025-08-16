// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Controllers/SkaterController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "Character/Components/SkaterMovementComponent.h"


void ASkaterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ACharacter* C = Cast<ACharacter>(InPawn))
	{
		if (auto* MC = C->GetCharacterMovement())
		{
			MovementComponent = Cast<USkaterMovementComponent>(MC);
		}
	}
	check(MovementComponent);
}

void ASkaterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IMC_Skate)
	{
		GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->AddMappingContext(IMC_Skate, 0);
	}
	auto* EIC = Cast<UEnhancedInputComponent>(InputComponent);

	if (IA_Steer)
	{
		EIC->BindAction(IA_Steer, ETriggerEvent::Triggered, this, &ASkaterController::OnSteerTriggered);
		EIC->BindAction(IA_Steer, ETriggerEvent::Completed, this, &ASkaterController::OnSteerCompleted);
	}
	if (IA_Move)
	{
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ASkaterController::OnMoveTriggered);
		EIC->BindAction(IA_Move, ETriggerEvent::Completed, this, &ASkaterController::OnMoveCompleted);
	}
	if (IA_Jump)
	{
		EIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &ASkaterController::OnJumpTriggered);

	}
}

void ASkaterController::OnSteerTriggered(const FInputActionValue& Value)
{
	MovementComponent->SetSteerAxis(Value.Get<float>());
}

void ASkaterController::OnSteerCompleted(const FInputActionValue& Value)
{
	MovementComponent->SetSteerAxis(Value.Get<float>());
}

void ASkaterController::OnMoveTriggered(const FInputActionValue& Value)
{
	MovementComponent->SetPressedInput(Value.Get<float>());
}

void ASkaterController::OnMoveCompleted(const FInputActionValue& Value)
{
	MovementComponent->SetPressedInput(Value.Get<float>());
}

void ASkaterController::OnJumpTriggered(const FInputActionValue& Value)
{
	MovementComponent->DoJump(false);
}
