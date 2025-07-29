// Fill out your copyright notice in the Description page of Project Settings.


#include "GuidedMissile.h"
#include "RocketEngine.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AGuidedMissile::AGuidedMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Rocket Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(true);
	Mesh->SetMobility(EComponentMobility::Movable);
	Mesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Missile Colldier"));
	CapsuleComponent->InitCapsuleSize(34.0f, 192.0f);
	CapsuleComponent->SetRelativeRotation(FRotator(90.0, 0.0, 0.0));
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);

	RocketEngine = CreateDefaultSubobject<URocketEngine>(TEXT("Rocket Engine"));

	SetPreviewValues();
}

void AGuidedMissile::SetPreviewValues()
{
	if (RocketEngineData)
	{
		//Set the preview values to the new engine data value.
		Preview_MaxFuel = RocketEngineData->MaxFuel;
		Preview_MaxSpeed = RocketEngineData->MaxSpeed;
		Preview_ComponentWeight = RocketEngineData->ComponentWeight;
		Preview_MaxAcceleration = RocketEngineData->MaxAcceleration;
	}
	else
	{
		//Set them to 0 when no engine data has been selected
		Preview_MaxFuel = 0.0f;
		Preview_MaxSpeed = 0.0f;
		Preview_ComponentWeight = 0.0f;
		Preview_MaxAcceleration = 0.0f;
	}
}

void AGuidedMissile::SetNewEngineData()
{
	SetPreviewValues();
	if (RocketEngine)
	{
		if (!RocketEngineData)
		{
			RocketEngine->EngineData = nullptr;
			UE_LOG(LogTemp, Warning, TEXT("Rocket Engine Data is not set!"));
			return;
		}
		//Send the engine the actual data
		RocketEngine->EngineData = RocketEngineData;
	}
}


// Called when the game starts or when spawned
void AGuidedMissile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGuidedMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#if WITH_EDITOR
void AGuidedMissile::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	SetNewEngineData();
}
#endif

void AGuidedMissile::PostLoad()
{
	Super::PostLoad();

	SetNewEngineData();
}