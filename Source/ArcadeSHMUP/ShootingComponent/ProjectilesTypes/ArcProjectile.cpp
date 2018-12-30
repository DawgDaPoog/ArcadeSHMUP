// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "ArcProjectile.h"
#include "Components/StaticMeshComponent.h"

AArcProjectile::AArcProjectile()
{
	Damage = 0.05f;
	ProjectileInitialSpeed = 0.f;
	bMoving = false;

	ZoneOfAttackEffect = CreateDefaultSubobject<UStaticMeshComponent>(FName("AreaOfAttack"));
	ZoneOfAttackEffect->SetupAttachment(RootComponent);
	ZoneOfAttackEffect->SetGenerateOverlapEvents(true);
	ZoneOfAttackEffect->bVisible = false;
	ZoneOfAttackEffect->SetCollisionProfileName("OverlapAll");
}


void AArcProjectile::BeginPlay()
{
	Super::BeginPlay();
	// Stay alive for 3 frames
	SetLifeSpan(2.f / 60.f);
}

void AArcProjectile::NotifyActorBeginOverlap(AActor * OtherActor)
{
	// Emmit the praticles to the enemy before dealing damage to him
	if (OtherActor->ActorHasTag("Enemy"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Initiating Particle Effects To Enemy"));
		EmmitParticleEffectsTo(OtherActor);
	}

	Super::NotifyActorBeginOverlap(OtherActor);
}


