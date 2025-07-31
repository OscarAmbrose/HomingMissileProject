// Fill out your copyright notice in the Description page of Project Settings.


#include "HeatSeekingBrain.h"
#include "HeatTarget.h"
#include "BaseRocket.h"
#include "Kismet/GameplayStatics.h"

void UHeatSeekingBrain::StartTimer(float Interval, bool bLoop)
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle_CheckTargets,
			this,
			&UHeatSeekingBrain::HandleTimerTick,
			Interval,
			bLoop
		);
	}
}

void UHeatSeekingBrain::StopCheckTargetsTimer()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_CheckTargets);
	}
}

void UHeatSeekingBrain::BeginPlay()
{
	StartTimer(0.2f, true);
}

//HUGE ROOM FOR OPTIMISATION HERE -- Running out of time -- Would like to visit this again. 
void UHeatSeekingBrain::HandleTimerTick()
{
	heatTargets.Empty();
	heatTargets = GetAllTargets();

	int TargetsFound = heatTargets.Num();
	UE_LOG(LogTemp, Warning, TEXT("HandlingTimerTick, Targets Found: %i"), TargetsFound);

	float VisionThreshold = FMath::Cos(FMath::DegreesToRadians(FieldOfViewAngle / 2.0f));

	float dotProduct;
	FVector targetDirection;
	FVector seekerDirection = GetOwner()->GetActorForwardVector();
	FVector seekerLocation = GetOwner()->GetActorLocation();

	UHeatTarget* bestTarget = nullptr;
	float bestTargetHeatScore = 0;

	float distance;
	float heatScore;

	//First, find all targets infront of the missile (in the aim cone)
	for (UHeatTarget* heatTarget : heatTargets)
	{
		AActor* targetOwner = heatTarget->GetOwner();
		targetDirection = (targetOwner->GetActorLocation() - seekerLocation);
		
		dotProduct = FVector::DotProduct(seekerDirection, targetDirection);

		distance = FVector::Dist(targetOwner->GetActorLocation(), seekerLocation);
		heatScore = heatTarget->HeatValue / FMath::Square(distance);

		//If not in vision code remove the object from the TArray.
		if (dotProduct <= VisionThreshold || heatScore < DetectableValue)
		{
			continue;
		}
		if (heatScore > bestTargetHeatScore)
		{
			bestTarget = heatTarget;
			bestTargetHeatScore = heatScore;
		}
	}
	if (!bestTarget) { targetLocation = seekerDirection * 100; return; }
	else
	{
		targetLocation = bestTarget->GetOwner()->GetActorLocation();
	}

	ABaseRocket* Rocket = Cast<ABaseRocket>(GetOwner());
	if (Rocket) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("SETTING TARGET LOCATION"));
		Rocket->CurrentTargetLocation = targetLocation; 
	}
}

TArray<UHeatTarget*> UHeatSeekingBrain::GetAllTargets()
{
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("HeatTarget"), TaggedActors);

	TArray<UHeatTarget*> heatTargetsFound = TArray<UHeatTarget*>();

	for (AActor* Actor : TaggedActors)
	{
		heatTargetsFound.Add(Actor->GetComponentByClass<UHeatTarget>());
	}

	return heatTargetsFound;
}
