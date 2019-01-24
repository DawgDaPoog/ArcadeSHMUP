// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyShielder.h"
#include "Components/SphereComponent.h"

AEnemyShielder::AEnemyShielder()
{
	// Default stats
	HitPoints = 50.f;

	PointsAwardedOnKill = 80;

	WeaponDropPriority = 2;

	// Creating default mesh for ShieldVolume
	ShieldVolume = CreateDefaultSubobject<USphereComponent>(FName("ShieldVolume"));
	ShieldVolume->SetupAttachment(RootComponent);
	ShieldVolume->SetCollisionProfileName(FName("OverlapAllDynamic"));
	ShieldVolume->SetGenerateOverlapEvents(true);

	ShieldVolume->OnComponentBeginOverlap.AddDynamic(this, &AEnemyShielder::OnShieldVolumeOverlapBegin);
	ShieldVolume->OnComponentEndOverlap.AddDynamic(this, &AEnemyShielder::OnShieldVolumeOverlapEnd);
}

void AEnemyShielder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Regain health
	CurrentHitpoints = FMath::Clamp(CurrentHitpoints + VolumeHealthPerSecondRegeneration*(1/60), 0.f, HitPoints);

	// Restore health of all enemies in range of volume
	TArray<AActor*> OverlappingActors;
	ShieldVolume->GetOverlappingActors(OverlappingActors);

	for (auto Actor : OverlappingActors)
	{
		if (Actor->ActorHasTag("Enemy"))
		{
			EmmitShieldParticleEffectsTo(Actor);
			Cast<AEnemy>(Actor)->RestoreHealth(VolumeHealthPerSecondRegeneration*(1 / 60));
		}
	}
}

void AEnemyShielder::OnShieldVolumeOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag("Enemy"))
	{
		Cast<AEnemy>(OtherActor)->SetInvincibility(true);
	}
}

void AEnemyShielder::OnShieldVolumeOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Enemy"))
	{
		Cast<AEnemy>(OtherActor)->SetInvincibility(false);
	}
}

void AEnemyShielder::SequenceDestroy()
{
	// Finding all actors in the vicinity of us
	TArray<AActor*> OverlappingActors;
	ShieldVolume->GetOverlappingActors(OverlappingActors);

	// If it is an enemy, make it vulnurable
	for (auto Actor : OverlappingActors)
	{
		if (Actor->ActorHasTag("Enemy"))
		{
			Cast<AEnemy>(Actor)->SetInvincibility(false);
		}
	}

	// Continue with the usual destruction sequence
	Super::SequenceDestroy();
}
