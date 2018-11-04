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


AProjectile* AArc::Fire()
{
	auto SpawnedProjectile = Super::Fire();
	Cast<AArcProjectile>(SpawnedProjectile)->InitiateSequenceDealDamage();

	BroadcastKnockback();

	return SpawnedProjectile;
}