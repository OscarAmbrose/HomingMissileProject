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
	Super::BeginPlay();

	StartTimer(0.05f, true);
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
	float bestTargetDistance = 0;
	float bestTargetHeatScore = 0;

	float distance;
	float heatScore;

	//First, find all targets infront of the missile (in the aim cone)
	for (UHeatTarget* heatTarget : heatTargets)
	{
		AActor* targetOwner = heatTarget->GetOwner();
		targetDirection = (targetOwner->GetActorLocation() - seekerLocation).GetSafeNormal();

		dotProduct = FVector::DotProduct(seekerDirection, targetDirection);

		distance = FVector::Dist(targetOwner->GetActorLocation(), seekerLocation);
		if (GEngine) GEngine->AddOnScreenDebugMessage(22, 5.f, FColor::Red, FString::Printf(TEXT("Distance: %.2f"), distance));
		heatScore = heatTarget->HeatValue / distance;

		UE_LOG(LogTemp, Warning, TEXT("Target Heat: %f, DetectableValue: %f"), heatScore, DetectableValue);
		UE_LOG(LogTemp, Warning, TEXT("Target Dot: %f, VisionThresh: %f"), dotProduct, VisionThreshold);


		//If not in vision code remove the object from the TArray.
		if (dotProduct <= VisionThreshold || heatScore < DetectableValue)
		{
			continue;
		}
		if (heatScore > bestTargetHeatScore)
		{
			UE_LOG(LogTemp, Warning, TEXT("NewBestTarget"));
			bestTarget = heatTarget;
			bestTargetDistance = distance;
			bestTargetHeatScore = heatScore;
		}
	}
	if (!bestTarget)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO Accepted Target Located"));
		targetLocation = seekerLocation + (seekerDirection * 100);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Accepted Target Located"));
		targetLocation = PredictTargetMotion(bestTarget, bestTargetDistance);
	}


	ABaseRocket* Rocket = Cast<ABaseRocket>(GetOwner());
	if (Rocket) 
	{ 
		Rocket->CurrentTargetLocation = targetLocation; 
	}

	DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), targetLocation, FColor::Red, false, 0.05f, 0, 2.0f);
	DrawDebugBox(GetWorld(), targetLocation, FVector(50, 50, 50), FQuat::Identity, FColor::Red, false, 0.05f, 0, 2.0f);
	DrawDebugCone(
		GetWorld(),
		GetOwner()->GetActorLocation(),
		GetOwner()->GetActorForwardVector(),
		40000.0f,
		FMath::DegreesToRadians(FieldOfViewAngle / 2),
		FMath::DegreesToRadians(FieldOfViewAngle / 2),
		12,
		FColor::Red,
		false,
		0.05f,
		0,
		3.0f
	);
}

FVector UHeatSeekingBrain::PredictTargetMotion(UHeatTarget* target, float distance)
{
	if (!target) { return FVector(); }
	AActor* targetActor = target->GetOwner();
	FVector resultLocation = targetActor->GetActorLocation();
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Distance: %.2f"), distance));
	float predictionTimeStep = FMath::Lerp(0.0f, predictionStepValue, FMath::Clamp(distance / predicitionFallOffStart, 0.0f, 1.0f));

	resultLocation += targetActor->GetVelocity() * predictionTimeStep;

	return resultLocation;
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
