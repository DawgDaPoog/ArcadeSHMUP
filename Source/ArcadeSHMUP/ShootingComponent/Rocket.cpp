// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Rocket.h"
#include "Engine/World.h"
#include "Projectile.h"

ARocket::ARocket()
{
	RateOfFire = 2.f;
	KnockbackForce = 30000.f;
	Damage = 40.f;
}

void ARocket::Fire()
{
	auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, FTransform(GetActorRotation(), GetActorLocation() + GetActorForwardVector()*5.f, FVector(1.f)));
	SpawnedProjectile->SetDamage(Damage);

	Super::Fire();
}

