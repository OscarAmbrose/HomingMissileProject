// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseRocket.generated.h"

class URocketStatManager;
struct FMissileComponentSlot;
class URocketMovement;
//struct URocketComponentSlot;

UCLASS(Blueprintable, BlueprintType)
class HOMINGMISSILEPROJECT_API ABaseRocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseRocket();

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<URocketStatManager> StatManager;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<URocketMovement> RocketMovement;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FMissileComponentSlot> ComponentSlots;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LaunchSpeed = 1000;

	/// <summary>
	/// Get a reference to the current stat manager.
	/// </summary>
	/// <returns>A reference to the current stat manager</returns>
	UFUNCTION(BlueprintPure, Category = "Stats")
	URocketStatManager* GetStatManager() const { return StatManager.Get(); }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ExplodeRocket();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CurrentTargetLocation = FVector();

	UFUNCTION(BlueprintCallable, Category = "Rocket")
	void LaunchRocket();

	UFUNCTION()
	bool ConsumeFuel(float fuelToConsume);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
