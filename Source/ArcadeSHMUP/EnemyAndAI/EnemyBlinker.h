// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAndAI/Enemy.h"
#include "EnemyBlinker.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AEnemyBlinker : public AEnemy
{
	GENERATED_BODY()
	
private:
	// Ray that is shot
	UPROPERTY(Category = Shooting, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AEnemyProjectile> RayToShoot;

	// Particles that are spawned at the place where blinker teleported from
	UPROPERTY(Category = Particles, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* ParticlesOnTeleportAfter;

	// Particles that are spawned at the place where blinker teleported to
	UPROPERTY(Category = Particles, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* ParticlesOnTeleportBefore;

	AEnemyProjectile* CurrentlySpawnedRay;
public:
	// To set up default parameters such as HP and other
	AEnemyBlinker();

	void BlinkTo(FVector Location);

	void InitialiseRayAt(FVector Location);
};
