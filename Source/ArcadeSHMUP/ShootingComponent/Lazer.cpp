// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Lazer.h"
#include "Engine/World.h"
#include "Projectile.h"

ALazer::ALazer()
{
	RateOfFire = 0.01f;
	KnockbackForce = 400.f;
	Damage = 0.07f;
}

void ALazer::Fire()
{
	auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, FTransform(GetActorRotation(), GetActorLocation() + GetActorForwardVector()*4.f, FVector(1.f)));
	SpawnedProjectile->SetDamage(Damage);

	Super::Fire(); // To broadcast fire delegate
}



