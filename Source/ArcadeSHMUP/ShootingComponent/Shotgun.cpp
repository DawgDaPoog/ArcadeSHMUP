// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Shotgun.h"
#include "Engine/World.h"
#include "Projectile.h"

AShotgun::AShotgun()
{
	RateOfFire = 1.f;
	KnockbackForce = 20000.f;
	Damage = 5.f;
}

AProjectile* AShotgun::Fire()
{
	if (Projectile)
	{
		AProjectile* SpawnedProjectile;
		for (int i = 0; i < AmountOfSpawnedProjectiles; i++)
		{
			float RotationSpread = FMath::RandRange(-Spread, Spread);
			SpawnedProjectile = Super::Fire();
			SpawnedProjectile->SetActorRotation(GetActorRotation()+FRotator(0.f,RotationSpread,0.f));
			SpawnedProjectile->SetDamage(Damage);
		}
	}
	BroadcastKnockback();
	return nullptr;
}
