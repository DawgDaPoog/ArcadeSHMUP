// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "ArcProjectile.h"
#include "Components/StaticMeshComponent.h"

AArcProjectile::AArcProjectile()
{
	Damage = 0.05f;
	ProjectileInitialSpeed = 0.f;

	ZoneOfAttackEffect = CreateDefaultSubobject<UStaticMeshComponent>(FName("AreaOfAttack"));
	ZoneOfAttackEffect->SetupAttachment(RootComponent);
	ZoneOfAttackEffect->SetGenerateOverlapEvents(true);
	ZoneOfAttackEffect->bVisible = false;
	ZoneOfAttackEffect->SetCollisionProfileName("OverlapAll");
}

void AArcProjectile::InitiateSequenceDealDamage()
{
	//Deal damage to all overlapping enemies
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	for (auto OverlappingActor : Actors)
	{
		if (OverlappingActor->ActorHasTag("Enemy"))
		{
			EmmitParticleEffectsTo(OverlappingActor);
			ReactToEnemy(OverlappingActor);
		}
	}
	
	
	SetLifeSpan(2.f/60.f);
}


