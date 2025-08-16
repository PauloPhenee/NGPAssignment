
#include "Controllers/SkaterPlayerState.h"

void ASkaterPlayerState::AddScore(int32 Value)
{
	_skateScore += Value;
	OnScoreChanged.Broadcast(_skateScore);
}

void ASkaterPlayerState::SetScoreValue(int32 NewValue)
{
	_skateScore = NewValue;
	OnScoreChanged.Broadcast(_skateScore);
}