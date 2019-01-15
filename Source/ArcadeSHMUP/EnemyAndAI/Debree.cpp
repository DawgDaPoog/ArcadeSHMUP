// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Debree.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
ADebree::ADebree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitPoints = 40.f;

	PointsAwardedOnKill = 20;

	WeaponDropPriority = 1;

	Mesh->SetPhysicsMaxAngularVelocity(10.f);
}

// Called when the game starts or when spawned
void ADebree::BeginPlay()
{
	Super::BeginPlay();

	InitialHitPoints = HitPoints;

	// Make it briefly invulnurable if it is a secondary spawn
	if (bIsSecondarySpawn)
	{
		bIsInvincible = true;

		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([this]()
		{
			bIsInvincible = false;
		});

		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.1f, false);
	}
	Mesh->SetPhysicsLinearVelocity(FMath::VRand().GetSafeNormal()*500.f);
	Mesh->SetPhysicsAngularVelocityInDegrees(FMath::VRand().GetSafeNormal()*FMath::RandRange(0.f,10.f));
}

void ADebree::SequenceDestroy()
{
	if (!bIsSecondarySpawn && Debree)
	{
		for (int i = 0; i <= FMath::RandRange(2, 4); i++)
		{
			FTransform DebreeTransform = FTransform(FRotator(FMath::RandRange(0.f, 360.f), FMath::RandRange(0.f, 360.f), FMath::RandRange(0.f, 360.f)), GetActorLocation(), FVector(FMath::RandRange(0.2f, 0.5f), FMath::RandRange(0.2f, 0.5f), 1.f));
			ADebree* DebreeActor = GetWorld()->SpawnActorDeferred<ADebree>(Debree, DebreeTransform);
			DebreeActor->HitPoints = InitialHitPoints / 3;
			DebreeActor->bIsSecondarySpawn = true;
			DebreeActor->FinishSpawning(DebreeTransform);
		}
	}
	Super::SequenceDestroy();
}

// Called every frame
void ADebree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	static const float SpeedLimit = 500.f;
	if (GetVelocity().Size() > SpeedLimit)
	{
		Mesh->SetPhysicsLinearVelocity(GetVelocity().GetSafeNormal()*SpeedLimit);
	}
}



