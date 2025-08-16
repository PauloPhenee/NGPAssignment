// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDWidget.h"
#include "Controllers/SkaterPlayerState.h"
#include "Components/TextBlock.h"


void UHUDWidget::NativeConstruct()
{
	APlayerController* PC = GetOwningPlayer();
	ASkaterPlayerState* PlayerState = PC->GetPlayerState<ASkaterPlayerState>();
	PlayerState->OnScoreChanged.AddDynamic(this, &UHUDWidget::HandleScoreChanged);
	ScoreText->SetText(FText::AsNumber(PlayerState->GetSkateScore()));
}

void UHUDWidget::HandleScoreChanged(int32 NewScore)
{
	ScoreText->SetText(FText::AsNumber(NewScore));
}
