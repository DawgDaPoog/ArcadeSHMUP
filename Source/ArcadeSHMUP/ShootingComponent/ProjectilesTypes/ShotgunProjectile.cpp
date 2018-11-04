// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "ShotgunProjectile.h"
#include "EnemyAndAI/Enemy.h"

AShotgunProjectile::AShotgunProjectile()
{
	Damage = 5.f;
	ProjectileInitialSpeed = 3000.f;
}

void AShotgunProjectile::ReactToEnemy(AActor * Enemy)
{
	Super::ReactToEnemy(Enemy);
	Destroy();
}


