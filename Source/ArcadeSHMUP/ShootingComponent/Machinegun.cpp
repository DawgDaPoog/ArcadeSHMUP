// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Machinegun.h"
#include "Engine/World.h"
#include "Projectile.h"


AMachinegun::AMachinegun()
{
	RateOfFire = 0.1f;
	KnockbackForce = 4500.f;
	Damage = 1.f;
}

void AMachinegun::Fire()
{
	auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, FTransform(GetActorRotation(), GetActorLocation() + GetActorForwardVector()*5.f, FVector(1.f)));
	SpawnedProjectile->SetDamage(Damage);

	Super::Fire(); // To broadcast fire delegate
}



