// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShootingComponent/Weapon.h"
#include "Lazer.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API ALazer : public AWeapon
{
	GENERATED_BODY()
		ALazer();

		virtual AProjectile* Fire() override;
		
		// Function to upgrade the weapon (Increase modificators)
		virtual void Upgrade() override;
	
};
