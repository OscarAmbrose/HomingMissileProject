// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GuidedMissile.generated.h"


class UCapsuleComponent;
class URocketEngineData;
class URocketEngine;

UCLASS()
class HOMINGMISSILEPROJECT_API AGuidedMissile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGuidedMissile();

	void SetPreviewValues();

	void SetNewEngineData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "!Missile")
	bool bIsRocketActive = false;

	//Preview Variables to show the stats when an engine type is selected in editor for convenience
	UPROPERTY(VisibleAnywhere, Category = "!Missile|Components|Engine")
	float Preview_MaxFuel;

	UPROPERTY(VisibleAnywhere, Category = "!Missile|Components|Engine")
	float Preview_ComponentWeight;

	UPROPERTY(VisibleAnywhere, Category = "!Missile|Components|Engine")
	float Preview_MaxAcceleration;

	UPROPERTY(VisibleAnywhere, Category = "!Missile|Components|Engine")
	float Preview_MaxSpeed;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void PostLoad() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "!Missile|Components|Engine", meta = (AllowPrivateAccess = "true"))
	URocketEngineData* RocketEngineData;

	UPROPERTY(BlueprintReadOnly, Category = "!Missile Components|Engine", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<URocketEngine> RocketEngine;

	UPROPERTY(Category = "Missile Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(Category = "Missile Components", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
