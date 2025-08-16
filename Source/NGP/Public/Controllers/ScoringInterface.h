// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ScoringInterface.generated.h"

UINTERFACE(MinimalAPI)
class UScoringInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class NGP_API IScoringInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Score")
	void OnScored(int32 Points);
};
