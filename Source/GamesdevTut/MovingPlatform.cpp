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
		GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
		GlobalStartLocation = GetActorLocation();

	}
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HasAuthority())
	{
		if (ActiveTriggers != 0)
		{
			FVector Location = GetActorLocation();
			Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			Location += MovementSpeed * DeltaSeconds * Direction;
			SetActorLocation(Location);
			float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float JourneyTravelled = (Location - GlobalStartLocation).Size();
			if (JourneyTravelled >= JourneyLength)
			{
				FVector temp = GlobalTargetLocation;
				GlobalTargetLocation = GlobalStartLocation;
				GlobalStartLocation = temp;
			}
		}
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
}

