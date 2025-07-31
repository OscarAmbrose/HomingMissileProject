// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseRocket.h"
#include "RocketStatManager.h"

// Sets default values
ABaseRocket::ABaseRocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatManager = CreateDefaultSubobject<URocketStatManager>(TEXT("StatManager"));

	UE_LOG(LogTemp, Warning, TEXT("%s"), FindComponentByTag(UActorComponent::StaticClass(), TEXT("StatManager")) ? TEXT("Found Manager") : TEXT("Didnt find Manager"));
}

// Called when the game starts or when spawned
void ABaseRocket::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

