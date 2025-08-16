// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ScoringObstacle.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include <Controllers/ScoringInterface.h>



AScoringObstacle::AScoringObstacle()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECC_WorldStatic);
	Mesh->SetCollisionResponseToAllChannels(ECR_Block);

	Coin = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin"));
	Coin->SetupAttachment(Root);
	Coin->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(Root);
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Trigger->SetCollisionObjectType(ECC_WorldDynamic);
	Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Trigger->SetGenerateOverlapEvents(true);

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AScoringObstacle::OnTriggerBeginOverlap);
}

void AScoringObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Coin->AddLocalRotation(FRotator(0.f, CoinRotationSpeed * DeltaTime, 0.f));
	if (!bCoinAvailable && CanAward())
	{
		bCoinAvailable = true;
		Coin->SetMaterial(0, GoldCoin);
	}
}

void AScoringObstacle::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UScoringInterface>() && bCoinAvailable)
	{
		IScoringInterface::Execute_OnScored(OtherActor, Points);
		LastAwardTime = GetWorld()->GetTimeSeconds();
		bCoinAvailable = false;
		Coin->SetMaterial(0, DarkCoin);
	}
}


