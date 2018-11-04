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

AProjectile* ARocket::Fire()
{
	BroadcastKnockback();
	return Super::Fire();
}

