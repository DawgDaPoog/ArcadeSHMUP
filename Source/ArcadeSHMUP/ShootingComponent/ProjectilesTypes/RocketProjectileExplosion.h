// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShootingComponent/Projectile.h"
#include "RocketProjectileExplosion.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API ARocketProjectileExplosion : public AProjectile
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ParticleEffects, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* ExplosionParticles;

	ARocketProjectileExplosion();

	virtual void BeginPlay() override;
};
