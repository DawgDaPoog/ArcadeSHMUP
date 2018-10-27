// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShootingComponent/Projectile.h"
#include "ShotgunProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AShotgunProjectile : public AProjectile
{
	GENERATED_BODY()

		AShotgunProjectile();
	
protected:
	virtual void ReactToEnemy(AActor* Enemy) override;
};
