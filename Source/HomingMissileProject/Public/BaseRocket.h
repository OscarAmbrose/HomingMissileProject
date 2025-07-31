// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseRocket.generated.h"

class URocketStatManager;

UCLASS(Blueprintable, BlueprintType)
class HOMINGMISSILEPROJECT_API ABaseRocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseRocket();

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<URocketStatManager> StatManager;

	/// <summary>
	/// Get a reference to the current stat manager.
	/// </summary>
	/// <returns>A reference to the current stat manager</returns>
	UFUNCTION(BlueprintPure, Category = "Stats")
	URocketStatManager* GetStatManager() const { return StatManager.Get(); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* CurrentTarget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
