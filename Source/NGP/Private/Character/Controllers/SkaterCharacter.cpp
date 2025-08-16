

#include "Character/Controllers/SkaterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void ASkaterCharacter::OnJump(ACharacter* Character)
{
	if (Character != this) return;
	AnimInstance->bIsJumping = true;
	UE_LOG(LogTemp, Log, TEXT("[%s] Jumping"), *FDateTime::Now().ToString(TEXT("%H:%M:%S.%s")));

}

void ASkaterCharacter::OnStartFalling(ACharacter* Character)
{
	if (Character != this) return;
	AnimInstance->bIsJumping = false;
	UE_LOG(LogTemp, Log, TEXT("[%s] Falling"), *FDateTime::Now().ToString(TEXT("%H:%M:%S.%s")));

}

void ASkaterCharacter::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = Cast<USkaterAnimInstance>(GetMesh()->GetAnimInstance());
	SkaterMC = Cast<USkaterMovementComponent>(GetCharacterMovement());
	SkaterMC->OnStartedFalling.AddDynamic(this, &ASkaterCharacter::OnStartFalling);
	SkaterMC->OnSkateJumping.AddDynamic(this, &ASkaterCharacter::OnJump);

}


