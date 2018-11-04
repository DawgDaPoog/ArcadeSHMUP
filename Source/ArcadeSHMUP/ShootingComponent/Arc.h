// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShootingComponent/Weapon.h"
#include "Arc.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AArc : public AWeapon
{
	GENERATED_BODY()

		AArc();

		virtual AProjectile* Fire() override;
	
	
};
