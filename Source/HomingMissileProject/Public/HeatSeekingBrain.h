// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseRocketComponent.h"
#include "HeatSeekingBrain.generated.h"

class UHeatTarget;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), Blueprintable, BlueprintType)
class HOMINGMISSILEPROJECT_API UHeatSeekingBrain : public UBaseRocketComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<UHeatTarget*> heatTargets;

	UPROPERTY(BlueprintReadWrite)
	FVector targetLocation = FVector();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FieldOfViewAngle = 60.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DetectableValue = 10000.0f;


public:
	// Optional: expose method to start the timer manually
	UFUNCTION(BlueprintCallable, Category = "Timer")
	void StartTimer(float Interval = 0.3f, bool bLoop = true);

	// Optional: stop the timer
	UFUNCTION(BlueprintCallable, Category = "Timer")
	void StopCheckTargetsTimer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle_CheckTargets;

	// Function to be called by the timer
	UFUNCTION()
	void HandleTimerTick();

	UFUNCTION()
	TArray<UHeatTarget*> GetAllTargets();

};
