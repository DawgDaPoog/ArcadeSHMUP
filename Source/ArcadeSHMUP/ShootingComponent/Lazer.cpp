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

AProjectile* ALazer::Fire()
{
	BroadcastKnockback();
	return Super::Fire(); 
}



