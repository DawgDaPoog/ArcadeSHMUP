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
	TSet<AActor*> Actors;
	GetOverlappingActors(Actors);
	for (auto OverlappingActor : Actors)
	{
		if (OverlappingActor->ActorHasTag("Enemy"))
		{
			ReactToEnemy(OverlappingActor);
		}
	}
	Destroy();
}


