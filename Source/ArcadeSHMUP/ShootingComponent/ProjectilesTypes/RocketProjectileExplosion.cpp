// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "RocketProjectileExplosion.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyAndAI/Enemy.h"
#include "TimerManager.h"
#include "Particles/ParticleSystemComponent.h"

ARocketProjectileExplosion::ARocketProjectileExplosion()
{
	// Creating a default subobject for the particle system component
	ExplosionParticles = CreateDefaultSubobject<UParticleSystemComponent>(FName("ExplosionParticles"));
	ExplosionParticles->SetupAttachment(RootComponent);
	ExplosionParticles->SetAutoActivate(false);

	Damage = 40.f;
}

void ARocketProjectileExplosion::BeginPlay()
{
	Super::Super::BeginPlay();

	// Deactivate moving
	bMoving = false;

	// Setting a timer to deactivate the mesh (damage zone) after 0.5 seconds.
	FTimerHandle TimerHandle;
	FTimerDelegate Delegate;
	Delegate.BindLambda([this]()
	{
		GetProjectileMesh()->SetGenerateOverlapEvents(false);
	});
	GetWorldTimerManager().SetTimer(TimerHandle, Delegate, 0.5f, false);
	
	// Lifespan to destroy the lingering actor after particle effects have played
	SetLifeSpan(3.f);

	// Activating explosion
	if (ExplosionParticles)
	{
		ExplosionParticles->Activate();
	}
}


