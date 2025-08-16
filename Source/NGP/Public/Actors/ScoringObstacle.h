// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoringObstacle.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class NGP_API AScoringObstacle : public AActor
{
	GENERATED_BODY()

public:
	AScoringObstacle();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Coin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin")
	UMaterial* GoldCoin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin")
	UMaterial* DarkCoin;

	// How many points to award when jumped over
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
	int32 Points = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score", meta = (ClampMin = "0.0"))
	float CooldownSeconds = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Coin", meta = (ClampMin = "0.0"))
	float CoinRotationSpeed = 10.0f;

	virtual void Tick(float DeltaTime) override;

protected:
	float LastAwardTime = -FLT_MAX;

	bool CanAward() { return GetWorld()->GetTimeSeconds() - LastAwardTime >= CooldownSeconds; }

	bool bCoinAvailable = true;

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
