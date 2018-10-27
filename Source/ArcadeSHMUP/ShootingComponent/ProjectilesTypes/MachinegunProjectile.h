// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShootingComponent/Projectile.h"
#include "MachinegunProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AMachinegunProjectile : public AProjectile
{
	GENERATED_BODY()

		AMachinegunProjectile();

protected:
	virtual void ReactToEnemy(AActor* Enemy) override;
	
};
