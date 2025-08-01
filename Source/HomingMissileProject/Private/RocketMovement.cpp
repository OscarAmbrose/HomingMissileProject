// Fill out your copyright notice in the Description page of Project Settings.

#include "RocketMovement.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
URocketMovement::URocketMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void URocketMovement::SetRocketTargetLocation(FVector newTargetLocation)
{
	TargetLocation = newTargetLocation;
}


bool URocketMovement::StartRocket()
{
	if (CurrentFuel == 0) { return false; }
	bEngineIsActive = true;
	bRocketIsLaunched = true;
	UE_LOG(LogTemp, Log, TEXT("Engine should start!"));
	return true;
}

bool URocketMovement::StartRocketWithVelocity(FVector StartVelocity)
{
	bool engineStarted = StartRocket();
	if (!engineStarted) { return false; }
	GetOwner()->SetActorRotation(StartVelocity.Rotation());
	Velocity = StartVelocity;
	return true;
}

void URocketMovement::OnStatUpdated(ERocketStatType StatChanged, float NewValue)
{
	switch(StatChanged)
	{
		case ERocketStatType::Acceleration:
			UE_LOG(LogTemp, Log, TEXT("Acceleration changed to %f"), NewValue);
			Acceleration = NewValue;
			break;
		case ERocketStatType::MaxSpeed:
			UE_LOG(LogTemp, Log, TEXT("MaxSpeed changed to %f"), NewValue);
			MaxSpeed = NewValue;
			break;
		case ERocketStatType::Manouverability:
			Manouverability = NewValue;
			break;
		case ERocketStatType::Weight:
			Weight = NewValue;
			break;
		case ERocketStatType::Fuel:
			UpdateMaxFuel(NewValue, true);
			break;
		default:
			break;
	}
}

void URocketMovement::UpdateMaxFuel(float newFuelVal, bool bIsFilling)
{
	MaxFuel = newFuelVal;
	if (bIsFilling) { CurrentFuel = MaxFuel; }
}

void URocketMovement::EngineActiveTick(float deltaTime)
{
	//Get current rotation and calculate next rotation
	FRotator oldRotation = GetOwner()->GetActorRotation();
	FRotator newRotation = GetNewRotation(deltaTime);
	//Update the rotation towards the desired target
	GetOwner()->SetActorRotation(newRotation);

	//Get the change in rotation.
	FRotator DeltaRot = (newRotation - oldRotation).GetNormalized();

	//Use the change in rotation to rotate the velocity

	Velocity = Velocity.Size() * GetOwner()->GetActorForwardVector();

	Velocity += (GetOwner()->GetActorForwardVector() * Acceleration * deltaTime);

	Velocity = Velocity.GetClampedToMaxSize(MaxSpeed);

	//UpdateLocation
	FVector ActorLocation = GetOwner()->GetActorLocation();
	ActorLocation += (Velocity * deltaTime);
	GetOwner()->SetActorLocation(ActorLocation);
}

void URocketMovement::EngineInactiveTick(float deltaTime)
{
	Velocity.Z += -900 * deltaTime;
	FVector ActorLocation = GetOwner()->GetActorLocation();
	ActorLocation += (Velocity * deltaTime);
	FRotator newRot = Velocity.GetSafeNormal().Rotation();
	GetOwner()->SetActorRotation(newRot);
	GetOwner()->SetActorLocation(ActorLocation);
}

bool URocketMovement::BurnFuel(float burntFuelAmount)
{
	bool hasEnoughFuel = (CurrentFuel -= burntFuelAmount) > 0;
	//UE_LOG(LogTemp, Log, TEXT("Burning fuel: %f"), burntFuelAmount);
	//UE_LOG(LogTemp, Log, TEXT("fuelLeft : %f"), CurrentFuel);
	//If not enough fuel, we need to deactivate the engine.
	if (!hasEnoughFuel) { bEngineIsActive = false; OnEngineDisabled.Broadcast(); }

	return hasEnoughFuel;
}

FRotator URocketMovement::GetNewRotation(float deltaTime)
{
	//Get owner location and rotation
	FVector OwnerLocation = GetOwner()->GetActorLocation();
	FRotator CurrentRotation = GetOwner()->GetActorRotation();

	//Use owner location and target location to find the desired rotation
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(OwnerLocation, TargetLocation);

	//Return the actual rotation possible towards the desired point, based on our manoeuvorability. TODO: Remove hardcoded 10.
	return FMath::RInterpConstantTo(CurrentRotation, TargetRotation, deltaTime, Manouverability);
}

void URocketMovement::SetRocketVelocity(FVector newVelocity)
{
}

// Called when the game starts
void URocketMovement::BeginPlay()
{
	Super::BeginPlay();



	URocketStatManager* statManager = Cast<URocketStatManager>(GetOwner()->FindComponentByTag(URocketStatManager::StaticClass(), TEXT("StatManager")));
	if (!statManager) { return; }
	statManager->OnStatChanged.AddDynamic(this, &URocketMovement::OnStatUpdated);
	// ...
	
}


// Called every frame
void URocketMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bRocketIsLaunched) { return; }

	if (!bEngineIsActive) 
	{ 
		EngineInactiveTick(DeltaTime);
		return; 
	}

	if (!BurnFuel(DeltaTime * (DEFAULT_FUEL_BURN_AMOUNT + (Weight * WEIGHT_FUEL_BURN_MODIFIER)))) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Ran out of Fuel"));
		EngineInactiveTick(DeltaTime);
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Running rocket!"));

	EngineActiveTick(DeltaTime);
}

