// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Arc.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "ProjectilesTypes/ArcProjectile.h"
AArc::AArc()
{
	RateOfFire = 1.f/60.f;
	KnockbackForce = 100.f;
	Damage = 0.25f;
}


AProjectile* AArc::Fire()
{
	BroadcastKnockback();
	return Super::Fire();
}

void AArc::Upgrade()
{
	SetDamageModificator(1.02f);
	SetProjectileSizeModificator(1.2f);
}
