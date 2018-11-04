// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShootingComponent/Projectile.h"
#include "RifleProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API ARifleProjectile : public AProjectile
{
	GENERATED_BODY()

		ARifleProjectile();

protected:
	virtual void ReactToEnemy(AActor* Enemy) override;
	
private:
	bool bHasHitEnemyAlready = false;
	
};
