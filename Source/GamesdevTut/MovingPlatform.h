// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class GAMESDEVTUT_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AMovingPlatform();
protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 20.0f;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget))
	FVector TargetLocation;

	FVector Direction;
	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;
	
};
