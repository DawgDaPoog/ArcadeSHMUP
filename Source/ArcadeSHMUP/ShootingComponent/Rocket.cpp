// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Rocket.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "ProjectilesTypes/RocketProjectile.h"

ARocket::ARocket()
{
	RateOfFire = 2.f;
	KnockbackForce = 30000.f;
	Damage = 20.f;
}

AProjectile* ARocket::Fire()
{
	BroadcastKnockback();
	auto Rocket = Super::Fire();
	Cast<ARocketProjectile>(Rocket)->SetExplosionRangeModificator(GetProjectileSizeModificator());

	return Rocket;
}

void ARocket::Upgrade()
{
	SetRateOfFireModificator(1.2f);
	SetDamageModificator(1.05f);
	SetProjectileSizeModificator(1.15f);
	SetKnockBackForceModificator(1.08f);
}

