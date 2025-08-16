// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/Controllers/SkaterAnimInstance.h"
#include "Character/Components/SkaterMovementComponent.h"
#include "Controllers/ScoringInterface.h"
#include "Controllers/SkaterPlayerState.h"
#include "SkaterCharacter.generated.h"


UCLASS()
class NGP_API ASkaterCharacter : public ACharacter, public IScoringInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnJump(ACharacter* Character);

	UFUNCTION()
	void OnStartFalling(ACharacter* Character);

	void OnScored_Implementation(int32 Points);

protected:
	//refs for easier access
	USkaterMovementComponent* SkaterMC = nullptr;

	USkaterAnimInstance* AnimInstance = nullptr;

	ASkaterPlayerState* PlayerState = nullptr;

	virtual void BeginPlay() override;
};
