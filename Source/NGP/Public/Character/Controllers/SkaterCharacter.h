// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/Controllers/SkaterAnimInstance.h"
#include "Character/Components/SkaterMovementComponent.h"
#include "SkaterCharacter.generated.h"


UCLASS()
class NGP_API ASkaterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnJump(ACharacter* Character);

	UFUNCTION()
	void OnStartFalling(ACharacter* Character);

protected:

	USkaterMovementComponent* SkaterMC = nullptr;

	USkaterAnimInstance* AnimInstance = nullptr;

	virtual void BeginPlay() override;

};
