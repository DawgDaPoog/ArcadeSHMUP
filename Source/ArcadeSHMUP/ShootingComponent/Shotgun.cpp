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

void AShotgun::Fire()
{
	if (Projectile)
	{
		for (int i = 0; i < AmountOfSpawnedProjectiles; i++)
		{
			float RotationSpread = FMath::RandRange(-Spread, Spread);
			auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, FTransform(GetActorRotation()+FRotator(0.f, RotationSpread,0.f), GetActorLocation() + GetActorForwardVector()*5.f, FVector(1.f)));
			SpawnedProjectile->SetDamage(Damage);
		}
	}
	Super::Fire();
}
