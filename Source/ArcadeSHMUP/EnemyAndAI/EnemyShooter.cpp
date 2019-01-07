// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "EnemyShooter.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyProjectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "ArcadeSHMUPGameMode.h"

AEnemyShooter::AEnemyShooter()
{
	HitPoints = 15.f;

	WeaponDropPriority = 1;

	ForceVectorNormal = FVector();

	MovementForce = 65000.f;

	MaximumVelocity = 500.f;
}

void AEnemyShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ForceVectorNormal);

	if (NewRot.Yaw > GetActorRotation().Yaw)
	SetActorRotation(GetActorRotation() + FRotator(0.f,2.f,0.f));
	else
	SetActorRotation(GetActorRotation() - FRotator(0.f, 2.f, 0.f));

	// Adding force to the mesh
	FVector DirectionVector = ForceVectorNormal - GetActorLocation();
	FVector Direction = DirectionVector.GetSafeNormal();

	// Adding force to move
	Mesh->AddForce(Direction*MovementForce);


	// Clamping our velocity if we go over the limit
	if (GetVelocity().Size() > MaximumVelocity)
	{
		Mesh->SetPhysicsLinearVelocity(GetVelocity().GetSafeNormal()*MaximumVelocity);
	}
}

void AEnemyShooter::ShootAt(FVector Location)
{
	// Spawn a projectile and set it's rotation to fit
	if (ProjectileToShoot)
	{
		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.Z = 260.f;

		FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Location);

		FTransform TransformToSpawn = FTransform(SpawnRotation, SpawnLocation, FVector(1.f));

		AEnemyProjectile* Projectile = GetWorld()->SpawnActorDeferred<AEnemyProjectile>(ProjectileToShoot, TransformToSpawn);
		Projectile->SetProjectileSpeedModificator(ProjectileSpeedModificator);
		Projectile->FinishSpawning(TransformToSpawn);
	}
}

void AEnemyShooter::SetForceVectorTo(FVector Location)
{
	ForceVectorNormal = Location;
}
