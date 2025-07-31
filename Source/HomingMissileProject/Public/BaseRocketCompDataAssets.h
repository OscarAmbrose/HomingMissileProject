// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RocketComponentStats.h"
#include "BaseRocketCompDataAssets.generated.h"

/**
 * Implementation of all of the base class data assets.
 */

UCLASS(BlueprintType)
class HOMINGMISSILEPROJECT_API UBaseRocketTriggerData : public URocketComponentDataBase
{
    GENERATED_BODY()

public:
    UBaseRocketTriggerData()
    {
        ComponentName = TEXT("Base Trigger Data");
        ComponentType = ERocketComponentType::Trigger;
        bHasAdditionalComponent = true;
        bHasMesh = false;
    }
};

UCLASS(BlueprintType)
class HOMINGMISSILEPROJECT_API UBaseRocketTrackingSystemData : public URocketComponentDataBase
{
    GENERATED_BODY()

public:
    UBaseRocketTrackingSystemData()
    {
        ComponentName = TEXT("Base Tracking System Data");
        ComponentType = ERocketComponentType::TrackingSystem;
        bHasAdditionalComponent = true;
        bHasMesh = true;
    }
};

UCLASS(BlueprintType)
class HOMINGMISSILEPROJECT_API UBaseRocketFinsData : public URocketComponentDataBase
{
    GENERATED_BODY()

public:
    UBaseRocketFinsData()
    {
        ComponentName = TEXT("Base Fins Data");
        ComponentType = ERocketComponentType::Fins;
        bHasAdditionalComponent = false;
        bHasMesh = true;
    }
};


UCLASS(BlueprintType)
class HOMINGMISSILEPROJECT_API UBaseRocketEngineData : public URocketComponentDataBase
{
	GENERATED_BODY()
	
public:
    UBaseRocketEngineData()
    {
        ComponentName = TEXT("Base Engine Data");
        ComponentType = ERocketComponentType::Engine;
        bHasAdditionalComponent = false;
        bHasMesh = true;
    }
};
