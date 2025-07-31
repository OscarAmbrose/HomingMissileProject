// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketStatManager.h"

// Sets default values for this component's properties
URocketStatManager::URocketStatManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	//ClearStats();

	//Add the tag which will be used to find the stat manager for other components.
	ComponentTags.Add(FName("StatManager"));

	//Reserve some memory to avoid dynamic reallocation.
	StatMap.Reserve(5);

	// ...
}

void URocketStatManager::GetStat(ERocketStatType Stat, float& foundValue, bool& success) const
{
	const float* Value = StatMap.Find(Stat);

	if (!Value)
	{
		success = false;
		foundValue = -1;
		return;
	}
	foundValue = *Value;
	success = true;
}

void URocketStatManager::ClearStats()
{
	StatMap.Empty();
}




float URocketStatManager::ModifyStat(ERocketStatType Stat, float ValueChange)
{
	//Ensure the stat exists with FindOrAdd, then change it by value change and store the value for the return. 
	float NewValue = StatMap.FindOrAdd(Stat) + ValueChange;
	StatMap.Add(Stat, NewValue);
	OnStatChanged.Broadcast(Stat, NewValue);
	return NewValue;
}

// Called when the game starts
void URocketStatManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URocketStatManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

