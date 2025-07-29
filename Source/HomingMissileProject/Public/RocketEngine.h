// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RocketEngineData.h"
#include "RocketEngine.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class HOMINGMISSILEPROJECT_API URocketEngine : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URocketEngine();

	//Data asset to be selected by the designer.
	UPROPERTY(BlueprintReadOnly, Category = "RocketEngine")
	TObjectPtr<URocketEngineData> EngineData;

	UPROPERTY(BlueprintReadOnly, Category = "RocketEngine")
	bool bIsRocketActive = false;

	UPROPERTY(BlueprintReadOnly, Category = "RocketEngine")
	float currentFuel;

	UPROPERTY()
	float MaxAcceleration;

	UPROPERTY()
	float Mass;

	UPROPERTY()
	TObjectPtr <UPrimitiveComponent> MissileRoot;


	UFUNCTION(BlueprintCallable, Category = "RocketEngine")
	bool SetRocketActive(bool bNewActive);

	/// <summary>
	/// Spend rocket fuel
	/// </summary>
	/// <param name="fuelSpent"> The amount of fuel you want to spend.</param>
	/// <returns>Returns whether you have enough fuel.</returns>
	UFUNCTION()
	bool SpendFuel(float fuelSpent);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "RocketEngine")
	inline bool RocketHasFuel() const { return (currentFuel > 0); }

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
