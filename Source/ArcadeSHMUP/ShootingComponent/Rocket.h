// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShootingComponent/Weapon.h"
#include "Rocket.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API ARocket : public AWeapon
{
	GENERATED_BODY()


		ARocket();

		virtual void Fire() override;
	
};
