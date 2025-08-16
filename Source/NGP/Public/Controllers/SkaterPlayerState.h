// Instead of using the default score (which is a float) we are using SkateScore just to make it simpler

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SkaterPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int32, NewScore);

UCLASS()
class NGP_API ASkaterPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	int32 GetSkateScore() const { return _skateScore; }

	UFUNCTION(BlueprintCallable)
	void AddScore(int32 Value);

	UFUNCTION(BlueprintCallable)
	void SetScoreValue(int32 NewValue);

	UPROPERTY(BlueprintAssignable)
	FOnScoreChanged OnScoreChanged;

protected:

	UPROPERTY()
	int32 _skateScore = 0;
};
