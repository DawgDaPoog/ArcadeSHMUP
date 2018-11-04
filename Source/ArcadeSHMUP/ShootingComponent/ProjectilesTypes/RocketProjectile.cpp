// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "RocketProjectile.h"
#include "EnemyAndAI/Enemy.h"

ARocketProjectile::ARocketProjectile()
{
	ProjectileInitialSpeed = 200.f;
	ProjectileCurrentSpeed = 500.f;
	ProjectileMaxSpeed = 3000.f;
	ProjectileAcceleration = 1000.f;
	Damage = 40.f;
}

void ARocketProjectile::ReactToEnemy(AActor * Enemy)
{
	Super::ReactToEnemy(Enemy);

	//Spawn AOE

	Destroy();
}


