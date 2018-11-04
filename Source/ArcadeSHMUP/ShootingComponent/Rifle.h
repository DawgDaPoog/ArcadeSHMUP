// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShootingComponent/Weapon.h"
#include "Rifle.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API ARifle : public AWeapon
{
	GENERATED_BODY()

	ARifle();

	virtual AProjectile* Fire() override;

	
	
};
