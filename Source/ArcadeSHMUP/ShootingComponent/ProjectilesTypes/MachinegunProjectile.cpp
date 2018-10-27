// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "MachinegunProjectile.h"

AMachinegunProjectile::AMachinegunProjectile()
{
	ProjectileInitialSpeed = 3000.f;
	Damage = 1.f;
}

void AMachinegunProjectile::ReactToEnemy(AActor * Enemy)
{
}
