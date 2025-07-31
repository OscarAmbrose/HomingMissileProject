// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "Components/ActorComponent.h"

UENUM(BlueprintType)
enum class ERocketStatType : uint8
{
	Health,
	Fuel,
	MaxSpeed UMETA(DisplayName = "Max Speed"),
	Weight,
	Acceleration
};

#include "RocketStatManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatChanged, ERocketStatType, StatChanged, float, NewValue);


UCLASS(ClassGroup = (Custom), meta = (DisplayName = "Stat Manager",
	Keywords = "statistics stats manager attributes components rocket missile health fuel weight",
	ToolTip = "Manages stats for rocket components, including max speed, weight, acceleration, manoeuvrability and destructivity."))
class HOMINGMISSILEPROJECT_API URocketStatManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URocketStatManager();

	/// <summary>
	/// Returns the value of a statistic held by the rocket.
	/// </summary>
	/// <param name="Stat">The stat you want to find.</param>
	/// <param name="foundValue">The Value of the stat (if it was found, otherwise it will return -1).</param>
	/// <param name="success">Returns true if a stat was found.</param>
	UFUNCTION(BlueprintPure, meta = (Category = "StatManager", KeyWords = "Rocket Statistics Manager Get Find"))
	void GetStat(ERocketStatType Stat, float& foundValue, bool& success) const;

	/// <summary>
	/// Changes a stat by the amount specified in Value Change.
	/// </summary>
	/// <param name="Stat">The stat you want to modify.</param>
	/// <param name="ValueChange">The amount you want to modify it by.</param>
	/// <returns>Returns the new stat value.</returns>
	UFUNCTION(BlueprintCallable, meta=(Category = "StatManager", KeyWords = "Rocket Statistics Manager Modify Add"))
	float ModifyStat(ERocketStatType Stat, float ValueChange);

	/// <summary>
	/// This event is called whenever a stat is modified.
	/// </summary>
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnStatChanged OnStatChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	TMap<ERocketStatType, float> StatMap;
};
