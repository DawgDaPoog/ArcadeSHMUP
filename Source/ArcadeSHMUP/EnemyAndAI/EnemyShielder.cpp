// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyShielder.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/World.h"
#include "Particles/ParticleSystem.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

AEnemyShielder::AEnemyShielder()
{
	// Default stats
	HitPoints = 150.f;

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

	// Restore health of every enemy in vicinity
	for (auto Actor : OverlappingActors)
	{
		if (Actor->ActorHasTag("Enemy"))
		{
			Cast<AEnemy>(Actor)->RestoreHealth(VolumeHealthPerSecondRegeneration*(1 / 60));
		}
	}

	// Update the particle effects targets and source points
	for (int i = 0; i < ParticlesToActorArray.Num(); i++)
	{
		if (ParticlesToActorArray[i].Particles)
		{
			ParticlesToActorArray[i].Particles->SetBeamSourcePoint(0, GetActorLocation(), 0);
			ParticlesToActorArray[i].Particles->SetBeamTargetPoint(0, ParticlesToActorArray[i].Enemy->GetActorLocation(), 0);
		}
	}
	

}

void AEnemyShielder::EmmitShieldParticleEffectsTo(AActor * Actor)
{
	if (ParticlesToEmmit)
	{
		UParticleSystemComponent* SpawnedParticles = UGameplayStatics::SpawnEmitterAttached(ParticlesToEmmit, Actor->GetRootComponent());
		FParticlesToActor NewItem;

		NewItem.Enemy = Actor;
		NewItem.Particles = SpawnedParticles;

		ParticlesToActorArray.Add(NewItem);

		SpawnedParticles->SetBeamSourcePoint(0, GetActorLocation(), 0);

		FVector BeamTarget = Actor->GetActorLocation();
		SpawnedParticles->SetBeamTargetPoint(0, Actor->GetActorLocation(), 0);

		SpawnedParticles->CustomTimeDilation = 10.f;
		
	}
}


void AEnemyShielder::ReactToPlayer(AArcadeSHMUPPawn * Player)
{
	// Empty to override usual functionality
}

void AEnemyShielder::OnShieldVolumeOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag("Enemy"))
	{
		// If we are in the vicinity of another shielder, don't make him invulnurable
		AEnemyShielder* ShielderCheck = Cast<AEnemyShielder>(OtherActor);
		if (ShielderCheck)
		{
			return;
		}

		// Set invincibility of the enemy to true and initialise particles to it
		Cast<AEnemy>(OtherActor)->SetInvincibility(true);
		EmmitShieldParticleEffectsTo(OtherActor);
	}
}

void AEnemyShielder::OnShieldVolumeOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Enemy"))
	{
		RemoveInvincibilityFrom(OtherActor);
	}
}

void AEnemyShielder::RemoveInvincibilityFrom(AActor * OtherActor)
{
	Cast<AEnemy>(OtherActor)->SetInvincibility(false);

	// Search the references by other actor's name and delete it
	for (int i = 0; i < ParticlesToActorArray.Num(); i++)
	{
		if (ParticlesToActorArray[i].Enemy->GetName() == OtherActor->GetName())
		{
			if (ParticlesToActorArray[i].Particles)
			{
				ParticlesToActorArray[i].Particles->DestroyComponent();
			}
			ParticlesToActorArray.RemoveAt(i);
			break;
		}
	}
}

void AEnemyShielder::SequenceDestroy()
{
	// Remove invincibility of all actors that have been granted invincibility by this shielder
	for (int i = 0; i < ParticlesToActorArray.Num(); i++)
	{
		Cast<AEnemy>(ParticlesToActorArray[i].Enemy)->SetInvincibility(false);
		ParticlesToActorArray[i].Particles->DestroyComponent();
		ParticlesToActorArray.RemoveAt(i);
	}

	// Continue with the usual destruction sequence
	Super::SequenceDestroy();
}
