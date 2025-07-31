// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RocketComponentStats.h"
#include "BaseRocketCompDataAssets.h"
#include "MissileComponentSlot.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct HOMINGMISSILEPROJECT_API FMissileComponentSlot
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName SlotName = TEXT("SlotName");

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ERocketComponentType SlotType = ERocketComponentType::Engine;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	URocketComponentDataBase* ComponentData;

	bool IsComponentDataValid() const 
	{ 
		ensure(ComponentData);
		return ComponentData ? true : false; 
	}
};

