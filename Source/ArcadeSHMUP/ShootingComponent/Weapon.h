// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

// Delegate that a player listens to. Applying knockback force upon recieving
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponDelegate, const float, KnockbackForce);


/*
* Basic weapon class to be derived from upon further childing 
**/
UCLASS()
class ARCADESHMUP_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	// Basic mesh
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	// Particles that play upon shooting 
	UPROPERTY(EditDefaultsOnly)
	class UParticleSystemComponent* ParticlesOnShot;

	// Projectile that is shot by this weapon
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AProjectile> Projectile;

	FWeaponDelegate OnFire;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Function that shoots projectile
	virtual AProjectile* Fire();

	// Weapon functionality default values
	float RateOfFire = 0.f;
	float ProjectileSpeed = 0.f;
	float Damage = 0.f;
	float KnockbackForce = 0.f;

	// Modificators, increasing or decreasing weapon's damage
	float RateOfFireModificator = 1.f;
	float DamageModificator = 1.f;
	float ProjectileSpeedModificator = 1.f;
	float KnockbackForceModificator = 1.f;
	float ProjectileSizeModificator = 1.f;

	// Boolean to determine if we can shoot or not
	bool bIsReloading = false;

	// Timer handle to reload
	struct FTimerHandle ReloadTimer;

	// Function to broadcast. Upon recieving this, Shooting Component will 
	void BroadcastKnockback();

private:

	// Functions to start and finish reloading
	void SetReloadTimer();
	void ReloadFinished();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Attempting to fire if we are not reloading
	void AttemptFire();

	// Function to upgrade the weapon (Increase modificators)
	virtual void Upgrade();

	// Asking the knockback force of this weapon
	float GetKnockBackForce();

	// Setting the knockback modificator
	void SetKnockBackForceModificator(float Modificator);

	// Asking for a fire rate of this weapon
	float GetRateOfFire();

	// Setting fire rate modificator
	void SetRateOfFireModificator(float Modificator);

	// Asking for projectile speed
	float GetProjectileSpeed();

	// Setting projectile speed modificator
	void SetProjectileSpeedModificator(float Modificator);

	// Asking for weapon damage
	float GetDamage();

	// Setting weapn damage modificator
	void SetDamageModificator(float Modificator);
};
