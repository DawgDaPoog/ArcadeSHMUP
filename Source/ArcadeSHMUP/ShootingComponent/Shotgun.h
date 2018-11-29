// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShootingComponent/Weapon.h"
#include "Shotgun.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AShotgun : public AWeapon
{
	GENERATED_BODY()
		AShotgun();

		virtual AProjectile* Fire() override;
	
public:
	// Potential projectile spread on shot
	float Spread = 20.f;
	int AmountOfSpawnedProjectiles = 10;
	

};
