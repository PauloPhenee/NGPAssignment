
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SkaterMovementComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkateFalling, ACharacter*, Character);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkateJumping, ACharacter*, Character);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NGP_API USkaterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skate|Speed")
	float MaxSkatingSpeed = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skate|Speed")
	float SkateAcceleration = 1200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skate|Speed")
	float SkateDeceleration = 1800.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skate|Steer")
	float TurnRate = 180.f;

	UPROPERTY(BlueprintAssignable, Category = "Skate|Events")
	FOnSkateFalling OnStartedFalling;

	UPROPERTY(BlueprintAssignable, Category = "Skate|Events")
	FOnSkateJumping OnSkateJumping;

	float CurrentForwardSpeed = 0.f;

	UFUNCTION(BlueprintCallable, Category = "Skate|Input")
	void SetPressedInput(float Value);

	UFUNCTION(BlueprintCallable, Category = "Skate|Input")
	void SetSteerAxis(float Axis);

	virtual void CalcVelocity(float DeltaTime, float Friction, bool bFluid, float BrakingDeceleration) override;

	virtual void OnMovementUpdated(float DeltaTime, const FVector& OldLocation, const FVector& OldVelocity) override;

	bool DoJump(bool bReplayingMoves) override;


protected:

	float _pressedInput = 0.0;

	//(left/right)
	float _steerAxis = 0.f;

	void Tick_Steer(float DeltaTime);
	void Tick_Speed(float DeltaTime, FVector OldLocation);
	void Tick_Move(float DeltaTime);
};
