
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SkaterAnimInstance.generated.h"


UCLASS(Blueprintable, BlueprintType)
class NGP_API USkaterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	bool bIsJumping = false;

};
