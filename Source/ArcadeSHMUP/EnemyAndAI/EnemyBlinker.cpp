// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "EnemyBlinker.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "TimerManager.h"

AEnemyBlinker::AEnemyBlinker()
{
	HitPoints = 60.f;

	WeaponDropPriority = 2;

	PointsAwardedOnKill = 100;
}

void AEnemyBlinker::BlinkTo(FVector Location)
{
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
		ParticlesOnTeleportAfter->Deactivate();
		ParticlesOnTeleportAfter->Activate();
	}
}

void AEnemyBlinker::InitialiseRayAt(FVector Location)
{
	if (RayToShoot)
	{
		// Find rotation to our target
		FRotator RotationToTarget = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Location);

		// Spawn the inactive ray
		CurrentlySpawnedRay = GetWorld()->SpawnActor<AEnemyProjectile>(RayToShoot, GetActorLocation(), RotationToTarget, FActorSpawnParameters());

		// Set a timer to activate the ray
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;

		TimerDelegate.BindLambda([this]() 
		{
			if (CurrentlySpawnedRay)
			{
				// Cast<ABlinkerRay>(CurrentlySpawnedRay)->ActivateRay();
			}
		});
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.5f, false);
	}
}
