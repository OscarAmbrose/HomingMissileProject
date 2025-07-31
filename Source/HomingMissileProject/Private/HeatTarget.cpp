// Fill out your copyright notice in the Description page of Project Settings.


#include "HeatTarget.h"

// Sets default values for this component's properties
UHeatTarget::UHeatTarget()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHeatTarget::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->Tags.Add(FName("HeatTarget"));
	// ...
	
}


// Called every frame
void UHeatTarget::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

