// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShootingComponent/Weapon.h"
#include "Machinegun.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AMachinegun : public AWeapon
{
	GENERATED_BODY()

		AMachinegun();

	virtual AProjectile* Fire() override;
	
	virtual void Upgrade() override;

};
