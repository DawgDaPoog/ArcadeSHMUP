// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponDelegate, const float, KnockbackForce);

UCLASS()
class ARCADESHMUP_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystemComponent* ParticlesOnShot;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AProjectile> Projectile;

	FWeaponDelegate OnFire;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Fire();

	float RateOfFire = 0.f;
	float ProjectileSpeed = 0.f;
	float Damage = 0.f;
	float KnockbackForce = 0.f;

	float RateOfFireModificator = 1.f;
	float DamageModificator = 1.f;
	float ProjectileSpeedModificator = 1.f;
	float KnockbackForceModificator = 1.f;
	float ProjectileSizeModificator = 1.f;

	bool bIsReloading = false;

	struct FTimerHandle ReloadTimer;
private:

	void SetReloadTimer();
	void ReloadFinished();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AttemptFire();

	void Upgrade();

	float GetKnockBackForce();
	void SetKnockBackForceModificator(float Modificator);

	float GetRateOfFire();
	void SetRateOfFireModificator(float Modificator);

	float GetProjectileSpeed();
	void SetProjectileSpeedModificator(float Modificator);

	float GetDamage();
	void SetDamageModificator(float Modificator);

	float GetProjectileSizeModificator();
	void SetProjectileSizeModificator(float Modificator);
};
