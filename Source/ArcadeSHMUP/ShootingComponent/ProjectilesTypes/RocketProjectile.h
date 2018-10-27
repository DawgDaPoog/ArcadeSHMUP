// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShootingComponent/Projectile.h"
#include "RocketProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API ARocketProjectile : public AProjectile
{
	GENERATED_BODY()

	ARocketProjectile();

protected:
	virtual void ReactToEnemy(AActor* Enemy) override;
	
};
