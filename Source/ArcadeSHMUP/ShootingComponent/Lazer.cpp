// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Lazer.h"
#include "Engine/World.h"
#include "Projectile.h"

ALazer::ALazer()
{
	RateOfFire = 1.f/60.f;
	KnockbackForce = 400.f;
	Damage = 0.4f;
}

AProjectile* ALazer::Fire()
{
	BroadcastKnockback();
	return Super::Fire(); 
}

void ALazer::Upgrade()
{
	SetDamageModificator(1.12f);
	SetProjectileSpeedModificator(1.1f);
	SetProjectileSizeModificator(1.3f);
}



