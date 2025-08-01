// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RocketStatManager.h"
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

UCLASS(Abstract)
class HOMINGMISSILEPROJECT_API URocketComponentDataBase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ERocketStatType, float> StatMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ComponentName = TEXT("DefaultName");

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ERocketComponentType ComponentType = ERocketComponentType::Engine;

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
		return *StatMap.Find(ERocketStatType::Weight);
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
};
