// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "EnemyBlinker.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "BlinkerRay.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyBlinkerAI.h"
#include "TimerManager.h"

AEnemyBlinker::AEnemyBlinker()
{
	HitPoints = 60.f;

	WeaponDropPriority = 3;

	PointsAwardedOnKill = 200;
}

void AEnemyBlinker::BeginPlay()
{
	Super::BeginPlay();

	// Find our controller
	MyController = Cast<AEnemyBlinkerAI>(GetController());

	// Ask for blink as we spawn
	if (MyController)
	{
		MyController->AskForBlink();
	}
}

void AEnemyBlinker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If we are focused set the rotation focus
	if (bIsFocused)
	{
		SetActorRotation(RotationFocus);
	}

	// If we have a spawned ray, set it's location and rotation to that of it's owner
	if (CurrentlySpawnedRay)
	{
		CurrentlySpawnedRay->SetActorLocation(GetActorLocation());
	}
	if (CurrentlySpawnedRay)
	{
		CurrentlySpawnedRay->SetActorRotation(GetActorRotation());
	}

	// Clamp our movement speed if we have too much velocity on mesh
	if (GetVelocity().Size() > 300.f)
	{
		Mesh->SetPhysicsLinearVelocity(GetVelocity().GetSafeNormal()*300.f);
	}
}

void AEnemyBlinker::BlinkTo(FVector Location)
{
	// Destroying the ray that we have spawned if we did
	if (CurrentlySpawnedRay)
	{
		CurrentlySpawnedRay->Destroy();
	}

	// Unfocus
	bIsFocused = false;

	// Spawn particles when we teleport from the place
	if (ParticlesOnTeleportBefore)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticlesOnTeleportBefore, GetActorLocation());
	}

	// Set actor location to the new, that has been set by the ai
	SetActorLocation(Location);

	// Spawn particles that play when we land at a new location
	if (ParticlesOnTeleportAfter)
	{
		UGameplayStatics::SpawnEmitterAttached(ParticlesOnTeleportAfter, RootComponent);
	}
}

void AEnemyBlinker::InitialiseRayAt(FVector Location)
{
	if (CurrentlySpawnedRay)
	{
		CurrentlySpawnedRay->Destroy();
	}
	if (RayToShoot)
	{
		// Find rotation to our target
		FRotator RotationToTarget = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Location);

		// Setting the rotation to target and telling blinker to focus
		RotationFocus = RotationToTarget;
		bIsFocused = true;

		// Spawn the inactive ray
		CurrentlySpawnedRay = GetWorld()->SpawnActor<AEnemyProjectile>(RayToShoot, GetActorLocation(), RotationToTarget, FActorSpawnParameters());

		// Set a timer to activate the ray after 1 sec
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;

		TimerDelegate.BindLambda([this]() 
		{
			if (CurrentlySpawnedRay)
			{
				Cast<ABlinkerRay>(CurrentlySpawnedRay)->ActivateRay();
			}
		});
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.f, false);
	}
}

void AEnemyBlinker::TakeDamage(float Damage)
{
	Super::TakeDamage(Damage);
	
	// If we are not invincible, request the AI controller to blink
	if (!bIsInvincible)
	{
		if (MyController)
		{
			MyController->AskForBlink();
		}
	}
}

void AEnemyBlinker::SequenceDestroy()
{
	if (CurrentlySpawnedRay)
	{
		CurrentlySpawnedRay->Destroy();
	}

	Super::SequenceDestroy();
}
