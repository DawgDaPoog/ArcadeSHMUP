// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Rifle.h"
#include "Engine/World.h"
#include "Projectile.h"


ARifle::ARifle()
{
	RateOfFire = 1.5f;
	KnockbackForce = 40000.f;
	Damage = 50.f;
}

AProjectile* ARifle::Fire()
{
	BroadcastKnockback();
	return Super::Fire();
}
