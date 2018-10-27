// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShootingComponent/Projectile.h"
#include "ArcProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AArcProjectile : public AProjectile
{
	GENERATED_BODY()
		AArcProjectile();

public:
	void InitiateSequenceDealDamage();
	
	
};
