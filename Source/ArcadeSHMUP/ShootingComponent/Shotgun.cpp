// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Shotgun.h"
#include "Engine/World.h"
#include "Projectile.h"

AShotgun::AShotgun()
{
	RateOfFire = 1.f;
	KnockbackForce = 20000.f;
	Damage = 3.7f;
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

void AShotgun::Upgrade()
{
	// Upgrading a shotgun
	SetRateOfFireModificator(1.05f);
	SetKnockBackForceModificator(1.0002f);
	Spread *= 0.9;
	AmountOfSpawnedProjectiles *= 1.2;
}
