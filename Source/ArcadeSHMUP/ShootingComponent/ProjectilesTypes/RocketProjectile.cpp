// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "RocketProjectile.h"
#include "EnemyAndAI/Enemy.h"
#include "Engine/World.h"
#include "RocketProjectileExplosion.h"

ARocketProjectile::ARocketProjectile()
{
	ProjectileInitialSpeed = 200.f;
	ProjectileCurrentSpeed = 500.f;
	ProjectileMaxSpeed = 3000.f;
	ProjectileAcceleration = 1000.f;
	Damage = 20.f;
}

void ARocketProjectile::ReactToEnemy(AActor * Enemy)
{
	Super::ReactToEnemy(Enemy);

	//Spawn AOE
	FTransform Transform = FTransform(GetActorRotation(),GetActorLocation(), FVector(1.f));
	auto SpawnedExplosion = GetWorld()->SpawnActorDeferred<AProjectile>(RocketExplosion, Transform);
	SpawnedExplosion->SetDamage(Damage*2.f);
	SpawnedExplosion->SetProjectileSizeModificator(ExplosionRangeModificator);
	SpawnedExplosion->FinishSpawning(Transform);

	Destroy();
}

void ARocketProjectile::SetExplosionRangeModificator(float Modificator)
{
	ExplosionRangeModificator *= Modificator;
}


