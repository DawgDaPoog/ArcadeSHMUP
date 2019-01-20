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
	class UParticleSystem* ParticlesOnTeleportAfter;

	// Particles that are spawned at the place where blinker teleported to
	UPROPERTY(Category = Particles, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* ParticlesOnTeleportBefore;

private:
	// Variable to store currently spawned ray for manipulations
	AEnemyProjectile* CurrentlySpawnedRay;

	// Rotation that the pawn has to maintain when it is focused
	FRotator RotationFocus;

	// boolean to know if blinker is focused (Needs to maintain a cerain rotation) or not
	bool bIsFocused = false;

	class AEnemyBlinkerAI* MyController;

	virtual void TakeDamage(float Damage) override;

	virtual void SequenceDestroy() override;
public:
	// To set up default parameters such as HP and other
	AEnemyBlinker();

	virtual void BeginPlay() override;

	// To set the proper location for the spawned projectile and set rotation focus point
	virtual void Tick(float DeltaTime) override;

	// Teleports this pawn to the given place
	void BlinkTo(FVector Location);

	// Initializes the attack at the location
	void InitialiseRayAt(FVector Location);
};
