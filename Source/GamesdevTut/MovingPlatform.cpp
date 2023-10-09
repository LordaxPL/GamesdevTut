// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	// Setting up ticking and the right mobility mode so the actor can move smoothly
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SMObject(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube'"));
	if (SMObject.Succeeded())
	{
		GetStaticMeshComponent()->SetStaticMesh(SMObject.Object);
	}
	
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		Location.X += MovementSpeed * DeltaSeconds;
		SetActorLocation(Location);
	}
}

