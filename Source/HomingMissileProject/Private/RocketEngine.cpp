// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketEngine.h"

// Sets default values for this component's properties
URocketEngine::URocketEngine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


bool URocketEngine::SetRocketActive(bool bNewActive)
{
	bIsRocketActive = bNewActive;
	return bIsRocketActive;
}


bool URocketEngine::SpendFuel(float fuelSpent)
{
	//If the rocket doesnt have enough fuel, disable the rocket
	if (!RocketHasFuel() || fuelSpent > currentFuel)
	{
		if (bIsRocketActive)
		{
			SetRocketActive(false);
		}
		return false;
	}

	//Otherwise spend the fuel
	currentFuel -= fuelSpent;
	return true;
}

// Called when the game starts
void URocketEngine::BeginPlay()
{
	Super::BeginPlay();

	//If engine data hasnt been set hit a breakpoint here.
	ensure(EngineData != nullptr);

	//Log a warning and continue play
	if (!EngineData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Rocket Engine Data is not set!"));
		return;
	}
	currentFuel = EngineData->MaxFuel;
	MaxAcceleration = EngineData->MaxAcceleration;

	MissileRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//Get the mass of the root component (Mesh) and get the mass for calculations
	if (MissileRoot)
	{
		Mass = MissileRoot->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Owner Mass: %f"), Mass);
	}
	
	SetRocketActive(true);
}


// Called every frame
void URocketEngine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector ForwardVector = GetOwner()->GetActorForwardVector();
	
	if (!SpendFuel(DeltaTime) || !bIsRocketActive)
	{
		return;
	}

	//FVector Force = ForwardVector * MaxAcceleration;

	FVector CurrentVelocity = MissileRoot->GetPhysicsLinearVelocity();
	FVector Forward = GetOwner()->GetActorForwardVector();

	FVector NewVelocity = FMath::Lerp(CurrentVelocity, Forward * MaxAcceleration, DeltaTime * 0.5);
	MissileRoot->SetPhysicsLinearVelocity(NewVelocity);

	// ...
}
