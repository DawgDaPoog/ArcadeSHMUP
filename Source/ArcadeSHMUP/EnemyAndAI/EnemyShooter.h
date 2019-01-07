// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAndAI/Enemy.h"
#include "EnemyShooter.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AEnemyShooter : public AEnemy
{
	GENERATED_BODY()

	UPROPERTY(Category = Shooting, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AEnemyProjectile> ProjectileToShoot;
public:
	AEnemyShooter();

	virtual void Tick(float DeltaTime) override;

	void ShootAt(FVector Location);

	void SetForceVectorTo(FVector Location);

private:
	// Direction to move
	FVector ForceVectorNormal;

	// Force to move with
	float MovementForce;

	// Max velocity possible
	float MaximumVelocity;

	float ProjectileSpeedModificator = 1.f;
};
