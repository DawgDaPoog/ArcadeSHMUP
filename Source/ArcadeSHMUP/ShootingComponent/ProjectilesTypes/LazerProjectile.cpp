// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "LazerProjectile.h"


ALazerProjectile::ALazerProjectile()
{
	Damage = 0.07f;
	ProjectileInitialSpeed = 5000.f;
}

void ALazerProjectile::ReactToEnemy(AActor * Enemy)
{
	Super::ReactToEnemy(Enemy);
}

