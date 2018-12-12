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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ZoneOfAttackEffect;
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Visual")
	void EmmitParticleEffectsTo(const AActor* Actor);

	void InitiateSequenceDealDamage();
	
	
};
