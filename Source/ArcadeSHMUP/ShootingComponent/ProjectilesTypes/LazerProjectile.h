// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShootingComponent/Projectile.h"
#include "LazerProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API ALazerProjectile : public AProjectile
{
	GENERATED_BODY()

		ALazerProjectile();

	virtual void ReactToEnemy(AActor* Enemy) override;
	
	
};
