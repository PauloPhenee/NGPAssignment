// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/SkaterMovementComponent.h"
#include "GameFramework/Character.h"


void USkaterMovementComponent::SetPressedInput(float Value)
{
	_pressedInput = Value;
}

void USkaterMovementComponent::SetSteerAxis(float Axis)
{
	_steerAxis = Axis;
}

void USkaterMovementComponent::CalcVelocity(float DeltaTime, float Friction, bool bFluid, float BrakingDeceleration)
{
	const float TargetSpeed = MaxSkatingSpeed * _pressedInput;

	CurrentForwardSpeed = FMath::Clamp(CurrentForwardSpeed, 0.f, MaxSkatingSpeed);

	const bool bAccelPhase = TargetSpeed > CurrentForwardSpeed;
	const float Rate = bAccelPhase ? SkateAcceleration : SkateDeceleration;
	const float Step = Rate * DeltaTime * (bAccelPhase ? +1.f : -1.f);

	if (bAccelPhase)
		CurrentForwardSpeed = FMath::Min(CurrentForwardSpeed + Step, TargetSpeed);
	else
		CurrentForwardSpeed = FMath::Max(CurrentForwardSpeed + Step, TargetSpeed);

	FVector Fwd = CharacterOwner ? CharacterOwner->GetActorForwardVector() : FVector::ForwardVector;

	if (IsMovingOnGround() && CurrentFloor.IsWalkableFloor())
	{
		Fwd = FVector::VectorPlaneProject(Fwd, CurrentFloor.HitResult.Normal).GetSafeNormal();
		if (Fwd.IsNearlyZero())
			Fwd = CharacterOwner ? CharacterOwner->GetActorForwardVector() : FVector::ForwardVector;
	}

	const float OldZ = Velocity.Z;
	Velocity = Fwd * CurrentForwardSpeed;
	Velocity.Z = OldZ;
}

void USkaterMovementComponent::OnMovementUpdated(float DeltaTime, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaTime, OldLocation, OldVelocity);
	Tick_Steer(DeltaTime);
	Tick_Speed(DeltaTime, OldLocation);

	if (IsFalling() && Velocity.Z <= 0.f)
	{
		OnStartedFalling.Broadcast(CharacterOwner);
		return;
	}
}

bool USkaterMovementComponent::DoJump(bool bReplayingMoves)
{
	if (IsMovingOnGround())
	{
		OnSkateJumping.Broadcast(CharacterOwner);
		return Super::DoJump(bReplayingMoves);
	}
	return false;
}

void USkaterMovementComponent::Tick_Steer(float DeltaTime)
{
	if (!CharacterOwner) return;

	const float DeltaYaw = _steerAxis * TurnRate * DeltaTime;
	FRotator NewRot = CharacterOwner->GetActorRotation();
	NewRot.Pitch = 0.f;
	NewRot.Roll = 0.f;
	NewRot.Yaw += DeltaYaw;
	CharacterOwner->SetActorRotation(NewRot);

}

void USkaterMovementComponent::Tick_Speed(float DeltaTime, FVector OldLocation)
{
	const FVector NewLocation = CharacterOwner->GetActorLocation();
	const FVector Delta = NewLocation - OldLocation;

	FVector Fwd = CharacterOwner->GetActorForwardVector();
	if (IsMovingOnGround() && CurrentFloor.IsWalkableFloor())
	{
		const FVector N = CurrentFloor.HitResult.Normal;
		Fwd = FVector::VectorPlaneProject(Fwd, N).GetSafeNormal();
		if (Fwd.IsNearlyZero()) Fwd = CharacterOwner->GetActorForwardVector();
	}

	const float ForwardAdvance = FVector::DotProduct(Delta, Fwd);
	const float ForwardSpeedMeasured = ForwardAdvance / DeltaTime;

	if (_pressedInput > 0.f)
	{
		if (ForwardSpeedMeasured <= 1.0f)
		{
			CurrentForwardSpeed = 0.f;
		}
	}
}

void USkaterMovementComponent::Tick_Move(float DeltaTime)
{
	if (Velocity.IsNearlyZero())
		return;

	FVector Delta = Velocity * DeltaTime;

	FHitResult Hit;
	SafeMoveUpdatedComponent(Delta, UpdatedComponent->GetComponentQuat(), true, Hit);

	if (Hit.IsValidBlockingHit())
	{
		SlideAlongSurface(Delta, 1.f - Hit.Time, Hit.Normal, Hit, true);
	}
}
