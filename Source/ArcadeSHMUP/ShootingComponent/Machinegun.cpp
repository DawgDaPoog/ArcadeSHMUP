// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Machinegun.h"
#include "Engine/World.h"
#include "Projectile.h"


AMachinegun::AMachinegun()
{
	RateOfFire = 0.1f;
	KnockbackForce = 4500.f;
	Damage = 3.f;
}

AProjectile* AMachinegun::Fire()
{
	BroadcastKnockback();
	return Super::Fire(); 
}

void AMachinegun::Upgrade()
{
	SetDamageModificator(1.15f);
	SetProjectileSpeedModificator(1.1f);
	SetRateOfFireModificator(1.15f);
	SetKnockBackForceModificator(1.1f);
}



