// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RocketStatManager.h"
#include "Components/ActorComponent.h"
#include "RocketMovement.generated.h"

#define DEFAULT_FUEL_BURN_AMOUNT 1.0f
#define WEIGHT_FUEL_BURN_MODIFIER 0.25f

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEngineDisabled);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOMINGMISSILEPROJECT_API URocketMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URocketMovement();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector TargetLocation = FVector(0,0,0);

	UPROPERTY(BlueprintReadOnly)
	FVector Velocity = FVector(0, 0, 0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bEngineIsActive = false;

	UPROPERTY(BlueprintReadOnly)
	float Weight = 100.0f;

	UPROPERTY(BlueprintReadOnly)
	float MaxSpeed = 10000.0f;

	UPROPERTY(BlueprintReadOnly)
	float Acceleration = 3600.0f;

	UPROPERTY(BlueprintReadOnly)
	float Manouverability = 16.0f;

	UFUNCTION(BlueprintCallable)
	void SetRocketTargetLocation(FVector newTargetLocation);

	UFUNCTION(BlueprintCallable)
	float GetCurrentFuel() const { return CurrentFuel; }

	UFUNCTION(BlueprintCallable)
	float GetMaxFuel() const { return MaxFuel; }

	UFUNCTION(BlueprintCallable)
	bool StartRocket();

	UFUNCTION(BlueprintCallable)
	bool StartRocketWithVelocity(FVector StartVelocity);

	UFUNCTION()
	void OnStatUpdated(ERocketStatType StatChanged, float NewValue);

	UPROPERTY(BlueprintAssignable, Category = "Rocket Events")
	FOnEngineDisabled OnEngineDisabled;

private:

	UFUNCTION()
	void UpdateMaxFuel(float newFuelVal, bool bIsFilling);

	UFUNCTION()
	void EngineActiveTick(float deltaTime);

	UFUNCTION()
	void EngineInactiveTick(float deltaTime);

	UPROPERTY()
	float MaxFuel = 100.0f;

	UPROPERTY()
	float CurrentFuel = 100.0f;

	UFUNCTION()
	bool BurnFuel(float fuelAmount);

	UFUNCTION()
	FRotator GetNewRotation(float deltaTime);

	UFUNCTION()
	void SetRocketVelocity(FVector newVelocity);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
