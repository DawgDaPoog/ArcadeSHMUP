// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "RifleProjectile.h"
#include "EnemyAndAI/Enemy.h"

ARifleProjectile::ARifleProjectile()
{
	ProjectileInitialSpeed = 4000.f;
	Damage = 50.f;
}

void ARifleProjectile::ReactToEnemy(AActor * Enemy)
{
	Super::ReactToEnemy(Enemy);
	if (bHasHitEnemyAlready)
	{
		Destroy();
	}
	else
	{
		bHasHitEnemyAlready = true;
	}
}


