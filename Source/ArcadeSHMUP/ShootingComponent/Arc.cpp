// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Arc.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "ProjectilesTypes/ArcProjectile.h"
AArc::AArc()
{
	RateOfFire = 0.01f;
	KnockbackForce = 100.f;
	Damage = 0.03f;
}


void AArc::Fire()
{
	auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, FTransform(GetActorRotation(), GetActorLocation() + GetActorForwardVector()*5.f, FVector(1.f)));
	SpawnedProjectile->SetDamage(Damage);
	Cast<AArcProjectile>(SpawnedProjectile)->InitiateSequenceDealDamage();

	Super::Fire(); // To broadcast fire delegate
}