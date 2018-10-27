// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "ArcProjectile.h"

AArcProjectile::AArcProjectile()
{
	Damage = 0.04f;
	ProjectileInitialSpeed = 0.f;
}

void AArcProjectile::InitiateSequenceDealDamage()
{
	//Deal damage to all overlapping enemies
	UE_LOG(LogTemp, Warning, TEXT("Being Destroyed"));
	Destroy();
}


