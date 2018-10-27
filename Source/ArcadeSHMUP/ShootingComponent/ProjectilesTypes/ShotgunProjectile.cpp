// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "ShotgunProjectile.h"

AShotgunProjectile::AShotgunProjectile()
{
	Damage = 5.f;
	ProjectileInitialSpeed = 3000.f;
}

void AShotgunProjectile::ReactToEnemy(AActor * Enemy)
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy Hit!"));
}


