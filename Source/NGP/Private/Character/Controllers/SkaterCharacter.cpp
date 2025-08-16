

#include "Character/Controllers/SkaterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void ASkaterCharacter::OnJump(ACharacter* Character)
{
	if (Character != this) return;
	AnimInstance->bIsJumping = true;
}

void ASkaterCharacter::OnStartFalling(ACharacter* Character)
{
	if (Character != this) return;
	AnimInstance->bIsJumping = false;
}

void ASkaterCharacter::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = Cast<USkaterAnimInstance>(GetMesh()->GetAnimInstance());
	SkaterMC = Cast<USkaterMovementComponent>(GetCharacterMovement());
	SkaterMC->OnStartedFalling.AddDynamic(this, &ASkaterCharacter::OnStartFalling);
	SkaterMC->OnSkateJumping.AddDynamic(this, &ASkaterCharacter::OnJump);
	PlayerState = GetPlayerState<ASkaterPlayerState>();
}

void ASkaterCharacter::OnScored_Implementation(int32 Points)
{
	PlayerState->AddScore(Points);
}


