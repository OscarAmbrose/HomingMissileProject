// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RocketComponentStats.generated.h"

UENUM(BlueprintType)
enum class ERocketComponentType : uint8
{
	Engine,
	Fins,
	Trigger,
	TrackingSystem UMETA(DisplayName = "Tracking System")
};

class UBaseRocketComponent;

USTRUCT(BlueprintType)
struct FRocketComponentData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float ComponentWeight = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Acceleration = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Manouverability = 16.6f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Destructivity = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxSpeed = 100.0f;
};

/**
 * 
 */
UCLASS(Abstract)
class HOMINGMISSILEPROJECT_API URocketComponentDataBase : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ComponentName = TEXT("DefaultName");

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ERocketComponentType ComponentType = ERocketComponentType::Engine;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRocketComponentData ComponentStats;

	UPROPERTY()
	bool bHasAdditionalComponent = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bHasAdditionalComponent", EditConditionHides))
	TSubclassOf<UBaseRocketComponent> ComponentToAdd;

	UPROPERTY()
	bool bHasMesh = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bHasMesh", EditConditionHides))
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bHasMesh", EditConditionHides))
	FName SocketToAttachTo;

	UFUNCTION(BlueprintPure, meta = (Keywords = "mass weight rocket component"))
	float GetComponentWeight() const
	{
		return ComponentStats.ComponentWeight;
	}

	UFUNCTION(BlueprintPure, meta = (Keywords = "Socket Attach Point Mesh Rocket Component"))
	FName GetComponentSocketToAttachTo() const
	{
		return SocketToAttachTo;
	}

	UFUNCTION(BlueprintPure, meta = (Keywords = "Component Rocket Additional"))
	TSubclassOf<UBaseRocketComponent> GetComponentComponentToAdd() const
	{
		return ComponentToAdd;
	}

	UFUNCTION(BlueprintPure, meta = (Keywords = "Acceleration speed rocket component"))
	float GetComponentAcceleration() const
	{
		return ComponentStats.Acceleration;
	}

	UFUNCTION(BlueprintPure, meta = (Keywords = "Manouverability turnrate rocket component"))
	float GetComponentManouverability() const
	{
		return ComponentStats.Manouverability;
	}

	UFUNCTION(BlueprintPure, meta = (Keywords = "Destructivity power damage rocket component"))
	float GetComponentDestructivity() const
	{
		return ComponentStats.Destructivity;
	}

	UFUNCTION(BlueprintPure, meta = (Keywords = "MaxSpeed Speed Max SpeedCap rocket component"))
	float GetComponentMaxSpeed() const
	{
		return ComponentStats.MaxSpeed;
	}
};
